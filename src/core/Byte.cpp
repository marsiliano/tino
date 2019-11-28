#include "Byte.hpp"

Byte::Byte(QString descr, int addr) : Element{ descr, addr } {}

Byte::Byte(QString descr, int addr, int8_t value) :
    Element{ descr, addr }, m_value{ value }
{
}

void Byte::setValue(int8_t value)
{
    if (m_value == value) {
        return;
    }

    m_value = value;
}

int16_t Byte::value() const
{
    return static_cast<int>(m_value);
}
