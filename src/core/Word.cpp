#include "Word.hpp"

Word::Word(QString descr, int value) : Element{ descr, 0 }
{
    setValue(value);
}

Word::Word(QString descr, Byte low, Byte high) :
    Element{ descr, 0 }, m_low{ low }, m_high{ high }
{
}

void Word::setValue(int16_t val)
{
    m_high.setValue(val >> 8);
    m_low.setValue(val & 0xFF);
}

int Word::value() const
{
    return (m_high.value() << 8) | m_low.value();
}

int Word::address() const noexcept
{
    return m_low.address();
}
