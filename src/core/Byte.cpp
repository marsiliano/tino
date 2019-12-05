#include "Byte.hpp"

Byte::Byte(QString name, QString descr, int addr) : Element{ name, descr, addr }
{
}

Byte::Byte(QString name, QString descr, int addr, int8_t value) :
    Element{ name, descr, addr }, m_value{ value }
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
