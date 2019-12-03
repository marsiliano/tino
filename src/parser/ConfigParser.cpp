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

    return Configuration{ readSettings(settings), readBlocks(protocol) };
}

Settings ConfigParser::readSettings(const QJsonObject &obj) const noexcept
{
    Settings s;

    s.portName = obj[Settings::Tags::port_name].toString(s.portName);

    s.baudRate = static_cast<QSerialPort::BaudRate>(
        obj[Settings::Tags::baud_rate].toInt(s.baudRate));

    s.breakEnabled =
        obj[Settings::Tags::break_enabled].toBool(s.breakEnabled);

    s.dataBits = static_cast<QSerialPort::DataBits>(
        obj[Settings::Tags::data_bits].toInt(s.dataBits));

    s.dataTerminalReady =
        obj[Settings::Tags::data_terminal_ready].toBool(s.dataTerminalReady);

    s.flowControl = static_cast<QSerialPort::FlowControl>(
        obj[Settings::Tags::flow_control].toInt(s.flowControl));

    s.requestToSend =
        obj[Settings::Tags::request_to_send].toBool(s.requestToSend);

    s.stopBits = static_cast<QSerialPort::StopBits>(
        obj[Settings::Tags::stop_bits].toInt(s.stopBits));

    return s;
}

Protocol ConfigParser::readBlocks(const QJsonObject &obj) const noexcept
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
    const auto size  = static_cast<size_t>(bits.size());
    for (size_t i = 0; i < size; ++i) {
        auto obj = bits[i].toObject();
        auto d   = obj.find(Tags::description)->toString();
        auto val = obj.find(Tags::defaultValue)->toBool();
        bitset->descriptions().push_back(d);
        bitset->setAt(i, val);
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
    auto value = obj.find(Tags::defaultValue)->toString().toInt(Q_NULLPTR, 16);
    auto addr  = obj.find(Tags::address)->toString().toInt(Q_NULLPTR, 16);
    return std::make_unique<Word>(description, addr, value);
}
