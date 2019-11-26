#include "Byte.hpp"

Byte::Byte(QString descr, int addr) : IElement{ descr, addr } {}

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
