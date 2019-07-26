#pragma once

#include <iostream>

namespace core
{
struct Settings {
    Settings()  = default;
    ~Settings() = default;
    bool operator==(const Settings &other);

    std::string portName;
    int Parity;
    int BaudRate;
    int DataBits;
    int StopBits;
    int ServerAddress;
};
} // namespace core
