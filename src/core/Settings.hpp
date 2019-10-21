#pragma once

#include <QSerialPort>

namespace core
{
class Settings
{
  public:
    Settings()                 = default;
    Settings(const Settings &) = default;
    Settings(Settings &&)      = default;
    ~Settings()                = default;

    Settings &operator=(const Settings &) = default;
    Settings &operator=(Settings &&) = default;

    bool operator==(const Settings &other) const
    {
        return baud_rate == other.baud_rate &&
               break_enabled == other.break_enabled &&
               data_bits == other.data_bits &&
               data_terminal_ready == other.data_terminal_ready &&
               error == other.error && stop_bits == other.stop_bits &&
               flow_control == other.flow_control &&
               request_to_send == other.request_to_send;
    }

    QSerialPort::BaudRate baud_rate{ QSerialPort::BaudRate::Baud115200 };
    bool break_enabled{ false };
    QSerialPort::DataBits data_bits{ QSerialPort::DataBits::UnknownDataBits };
    bool data_terminal_ready{ false };
    QSerialPort::SerialPortError error{ QSerialPort::SerialPortError::NoError };
    QSerialPort::StopBits stop_bits{ QSerialPort::StopBits::OneStop };
    QSerialPort::FlowControl flow_control{
        QSerialPort::FlowControl::NoFlowControl
    };
    QSerialPort::Parity parity{ QSerialPort::Parity::NoParity };
    bool request_to_send{ false };
};

} // namespace core
