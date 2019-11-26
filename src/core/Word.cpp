#include "Word.hpp"

Word::Word(QString descr, int addr) : Element{ descr, addr } {}

Word::Word(QString descr, const QPair<Byte, Byte> &value) :
    Element{ descr, 0 }, m_bytes{ value }
{
}

QPair<Byte, Byte> Word::bytes() const
{
    return m_bytes;
}

void Word::setBytes(const QPair<Byte, Byte> &value)
{
    if (m_bytes == value) {
        return;
    }

    m_bytes = value;
}

int Word::address() const noexcept
{
    return m_bytes.first.address();
}
