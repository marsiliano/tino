#include "Byte.hpp"

int Byte::address() const
{
    return m_address;
}

QString Byte::description() const
{
    return m_description;
}

int Byte::value() const
{
    return m_value;
}
