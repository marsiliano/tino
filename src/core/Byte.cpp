#include "Byte.hpp"

Byte::Byte(QString descr, int addr) : Element{ descr, addr } {}

Byte::Byte(QString descr, int addr, int value) :
    Element{ descr, addr }, m_value{ value }
{
}

int Byte::value() const
{
    return m_value;
}

void Byte::setValue(int value)
{
    if (m_value == value) {
        return;
    }

    m_value = value;
}
