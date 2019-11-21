#pragma once

#include <QSerialPort>

class Settings
{
  public:
    Settings()                 = default;
    Settings(const Settings &) = default;
    Settings(Settings &&)      = default;
    ~Settings()                = default;

    Settings &operator=(const Settings &) = default;
    Settings &operator=(Settings &&) = default;

    bool operator==(const Settings &other) const;
    bool operator!=(const Settings &other) const;

    struct Tags {
        constexpr static const auto port_name           = "portName";
        constexpr static const auto baud_rate           = "baudRate";
        constexpr static const auto break_enabled       = "breakEnabled";
        constexpr static const auto data_bits           = "dataBits";
        constexpr static const auto data_terminal_ready = "dataTerminalReady";
        constexpr static const auto flow_control        = "flowControl";
        constexpr static const auto parity              = "parity";
        constexpr static const auto request_to_send     = "requestToSend";
        constexpr static const auto stop_bits           = "stopBits";
    };

    QString port_name{};
    QSerialPort::BaudRate baud_rate{ QSerialPort::BaudRate::Baud115200 };
    bool break_enabled{ false };
    QSerialPort::DataBits data_bits{ QSerialPort::DataBits::UnknownDataBits };
    bool data_terminal_ready{ false };
    QSerialPort::FlowControl flow_control{
        QSerialPort::FlowControl::NoFlowControl
    };
    QSerialPort::Parity parity{ QSerialPort::Parity::NoParity };
    bool request_to_send{ false };
    QSerialPort::StopBits stop_bits{ QSerialPort::StopBits::OneStop };
};
