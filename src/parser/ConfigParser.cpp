#include "ConfigParser.hpp"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

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
    const auto settings = obj.find("settings")->toObject();
    const auto blocks   = obj.find("blocks")->toArray();

    if (settings.isEmpty() && blocks.isEmpty()) {
        return {};
    }

    return Configuration{ read_settings(settings), read_blocks(blocks) };
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

Protocol ConfigParser::read_blocks(const QJsonArray &array) const noexcept
{
    Protocol ret;
    foreach (auto v, array) {
        Block blk;
        const auto block = v.toObject();
        blk.description  = block.find("description")->toString();

        const auto groups = block.find("groups")->toArray();
        foreach (auto g, groups) {
            Group grp;
            grp.description = g.toObject().find("description")->toString();
            const auto bits = g.toObject().find("bits")->toArray();

            //            Byte byte;
            //            foreach (auto b, bits) {
            //                Flag flag;
            //                flag.description =
            //                b.toObject().find("description")->toString();
            //                flag.default_value =
            //                    b.toObject().find("defaultValue")->toBool();
            //                byte.flags.push_back(flag);
            //            }
            //            grp.bytes.push_back(byte);
            blk.groups.push_back(grp);
        }

        ret.blocks.push_back(blk);
    }

    return ret;
}
