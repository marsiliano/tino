#include "ConfigParser.hpp"

#include <Bitset.hpp>
#include <Byte.hpp>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <Word.hpp>
#include <functional>

Configuration::Configuration(Settings &&set, Protocol &&prot) :
    settings{ set }, protocol{ std::move(prot) }
{
}

bool Configuration::operator==(const Configuration &other) const
{
    return settings == other.settings && protocol == other.protocol;
}

Configuration ConfigParser::parse(const QString &filename)
{
    QFile file{ filename };
    if (!file.exists()) {
        throw std::logic_error("file not exists");
    }

    if (!file.open(QIODevice::ReadOnly)) {
        throw std::logic_error("can't open file");
    }

    QJsonParseError error{};
    const auto content = file.readAll();
    auto doc           = QJsonDocument::fromJson(content, &error);
    if (error.error != QJsonParseError::NoError) {
        throw std::logic_error("error parsing json " +
                               std::to_string(error.error));
    }

    const auto obj      = doc.object();
    const auto settings = obj.find(Tags::settings)->toObject();
    const auto protocol = obj.find(Tags::protocol)->toObject();

    if (settings.isEmpty() && protocol.isEmpty()) {
        return {};
    }

    return Configuration{ read_settings(settings), read_blocks(protocol) };
}

Settings ConfigParser::read_settings(const QJsonObject &obj) const noexcept
{
    Settings s;

    s.port_name = obj[Settings::Tags::port_name].toString(s.port_name);

    s.baud_rate = static_cast<QSerialPort::BaudRate>(
        obj[Settings::Tags::baud_rate].toInt(s.baud_rate));

    s.break_enabled =
        obj[Settings::Tags::break_enabled].toBool(s.break_enabled);

    s.data_bits = static_cast<QSerialPort::DataBits>(
        obj[Settings::Tags::data_bits].toInt(s.data_bits));

    s.data_terminal_ready =
        obj[Settings::Tags::data_terminal_ready].toBool(s.data_terminal_ready);

    s.flow_control = static_cast<QSerialPort::FlowControl>(
        obj[Settings::Tags::flow_control].toInt(s.flow_control));

    s.request_to_send =
        obj[Settings::Tags::request_to_send].toBool(s.request_to_send);

    s.stop_bits = static_cast<QSerialPort::StopBits>(
        obj[Settings::Tags::stop_bits].toInt(s.stop_bits));

    return s;
}

Protocol ConfigParser::read_blocks(const QJsonObject &obj) const noexcept
{
    Protocol ret;
    const auto array = obj.find(Tags::blocks)->toArray();
    if (array.isEmpty()) {
        return ret;
    }

    foreach (auto v, array) {
        Block blk;
        const auto block  = v.toObject();
        blk.description   = block.find(Tags::description)->toString();
        const auto groups = block.find(Tags::groups)->toArray();
        foreach (auto g, groups) {
            auto type = g.toObject().find(Tags::type)->toString();
            std::unique_ptr<Element> element;
            if (type == Tags::bitsarray) {
                element = std::move(makeBitset(g.toObject()));
            } else if (type == Tags::byte) {
                element = std::move(makeByte(g.toObject()));
            } else if (type == Tags::word) {
                element = std::move(makeWord(g.toObject()));
            } else {
                qWarning() << "tag not handled";
            }
            blk.elements.emplace_back(std::move(element));
        }
        ret.blocks.emplace_back(std::move(blk));
    }
    return ret;
}

std::unique_ptr<Bitset> ConfigParser::makeBitset(const QJsonObject &obj) const
{
    auto description = obj.find(Tags::description)->toString();
    auto address     = obj.find(Tags::address)->toString().toInt(Q_NULLPTR, 16);
    auto element     = std::make_unique<Bitset>(description, address);
    auto bits        = obj.find(Tags::bit)->toArray();
    auto bitset      = dynamic_cast<Bitset *>(element.get());
    foreach (auto a, bits) {
        auto d   = obj.find(Tags::description)->toString();
        auto val = obj.find(Tags::defaultValue)->toBool();
        bitset->bitsDescriptions.push_back(d);
        bitset->bits.set(0, val);
    }

    return element;
}

std::unique_ptr<Byte> ConfigParser::makeByte(const QJsonObject &obj) const
{
    auto description = obj.find(Tags::description)->toString();
    auto address     = obj.find(Tags::address)->toString().toInt(Q_NULLPTR, 16);
    auto defaultValue = obj.find(Tags::defaultValue)->toString().toInt();
    auto element      = std::make_unique<Byte>(description, address);
    element->setValue(defaultValue);
    return element;
}

std::unique_ptr<Word> ConfigParser::makeWord(const QJsonObject &obj) const
{
    auto description = obj.find(Tags::description)->toString();
    auto bytes       = obj.find(Tags::bytes)->toArray();
    QPair<Byte, Byte> values;
    if (bytes.size() != 2) {
        qWarning() << "error while make word";
        return std::make_unique<Word>("dummy", 0);
    }

    auto b0 = bytes[0].toObject();
    auto a0 = b0.find(Tags::address)->toString().toInt(Q_NULLPTR, 16);
    auto d0 = b0.find(Tags::description)->toString();
    auto v0 = b0.find(Tags::defaultValue)->toString().toInt();

    auto b1 = bytes[0].toObject();
    auto a1 = b1.find(Tags::address)->toString().toInt(Q_NULLPTR, 16);
    auto d1 = b1.find(Tags::description)->toString();
    auto v1 = b1.find(Tags::defaultValue)->toString().toInt();

    values.first  = Byte(d0, a0, v0);
    values.second = Byte(d1, a1, v1);

    auto element = std::make_unique<Word>(description, values);
    return element;
}
