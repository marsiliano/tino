#include "ConfigParser.hpp"

#include <QFile>
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

    return Configuration{ std::move(read_settings(settings)), {} };
}

Settings ConfigParser::read_settings(const QJsonObject &obj) const noexcept
{
    Settings s;
    s.baud_rate = static_cast<QSerialPort::BaudRate>(
        obj[Settings::Tags::baud_rate].toInt());

    s.break_enabled = obj[Settings::Tags::break_enabled].toBool();

    s.data_bits = static_cast<QSerialPort::DataBits>(
        obj[Settings::Tags::data_bits].toInt());

    s.data_terminal_ready = obj[Settings::Tags::data_terminal_ready].toBool();

    s.flow_control = static_cast<QSerialPort::FlowControl>(
        obj[Settings::Tags::flow_control].toInt());

    s.request_to_send = obj[Settings::Tags::request_to_send].toBool();

    s.stop_bits = static_cast<QSerialPort::StopBits>(
        obj[Settings::Tags::stop_bits].toInt());

    return s;
}
