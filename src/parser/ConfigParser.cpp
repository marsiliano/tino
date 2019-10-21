#include "ConfigParser.hpp"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

core::Settings ConfigParser::parse(const QString &filename)
{
    QFile file{ filename };
    if (!file.exists()) {
        throw std::logic_error("file not exists");
    }

    if (!file.open(QIODevice::ReadOnly)) {
        throw std::logic_error("can't open file");
    }

    QJsonParseError error;
    const auto content = file.readAll();
    auto doc           = QJsonDocument::fromJson(content, &error);
    if (error.error != QJsonParseError::NoError) {
        throw std::logic_error("error parsing json " +
                               std::to_string(error.error));
    }

    const auto obj      = doc.object();
    const auto settings = obj.find("settings")->toObject();
    if (settings.isEmpty()) {
        return {};
    }

    return read_settings(settings);
}

core::Settings ConfigParser::read_settings(const QJsonObject &obj) const
    noexcept
{
    core::Settings s;
    s.baud_rate = static_cast<QSerialPort::BaudRate>(
        obj[core::Settings::Tags::baud_rate].toInt());

    s.break_enabled = obj[core::Settings::Tags::break_enabled].toBool();

    s.data_bits = static_cast<QSerialPort::DataBits>(
        obj[core::Settings::Tags::data_bits].toInt());

    s.data_terminal_ready =
        obj[core::Settings::Tags::data_terminal_ready].toBool();

    s.flow_control = static_cast<QSerialPort::FlowControl>(
        obj[core::Settings::Tags::flow_control].toInt());

    s.request_to_send = obj[core::Settings::Tags::request_to_send].toBool();

    s.stop_bits = static_cast<QSerialPort::StopBits>(
        obj[core::Settings::Tags::stop_bits].toInt());

    return s;
}
