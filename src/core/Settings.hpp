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

    QString portName{};
    QSerialPort::BaudRate baudRate{ QSerialPort::BaudRate::Baud115200 };
    bool breakEnabled{ false };
    QSerialPort::DataBits dataBits{ QSerialPort::DataBits::UnknownDataBits };
    bool dataTerminalReady{ false };
    QSerialPort::FlowControl flowControl{
        QSerialPort::FlowControl::NoFlowControl
    };
    QSerialPort::Parity parity{ QSerialPort::Parity::NoParity };
    bool requestToSend{ false };
    QSerialPort::StopBits stopBits{ QSerialPort::StopBits::OneStop };
};
