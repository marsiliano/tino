#include "Word.hpp"

Word::Word(QString descr, int16_t value) : Element{ descr, 0 }
{
    setValue(value);
}

Word::Word(QString descr, int addr, uint8_t low, uint8_t high) :
    Element{ descr, addr }, m_low{ low }, m_high{ high }
{
}

void Word::setValue(int16_t val)
{
    m_high = val >> 8;
    m_low  = val & 0xFF;
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
