#pragma once

#include <QSerialPortInfo>

namespace core
{
class Settings
{
    Settings()                 = default;
    Settings(const Settings &) = default;
    Settings(Settings &&)      = default;
    ~Settings()                = default;

    Settings &operator=(const Settings &) = default;
    Settings &operator=(Settings &&) = default;

    QSerialPortInfo info;
};

} // namespace core
