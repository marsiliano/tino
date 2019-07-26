#include "Settings.hpp"

bool core::Settings::operator==(const Settings &other)
{
    return (portName == other.portName && Parity == other.Parity &&
            BaudRate == other.BaudRate && DataBits == other.DataBits &&
            StopBits == other.StopBits && ServerAddress == other.ServerAddress);
}
