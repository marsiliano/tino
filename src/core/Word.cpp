#include "Word.hpp"

Word::Word(QString name, QString descr, int addr, int16_t value) :
    Element{ name, descr, addr }
{
    m_high = value >> 8;
    m_low  = value & 0xFF;
}

Word::Word(QString name, QString descr, int addr, uint8_t low, uint8_t high) :
    Element{ name, descr, addr }, m_low{ low }, m_high{ high }
{
}

void Word::setValue(int8_t val)
{
    setValue(static_cast<int16_t>(val));
}

void Word::setValue(int16_t value)
{
    m_high = value >> 8;
    m_low  = value & 0xFF;
}

int16_t Word::value() const
{
    return (m_high << 8) | m_low;
}

uint8_t Word::low() const noexcept
{
    return m_low;
}

uint8_t Word::high() const noexcept
{
    return m_high;
}
