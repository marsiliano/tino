#include "Word.hpp"

QString Word::description() const
{
    return m_description;
}

QPair<Byte, Byte> Word::bytes() const
{
    return m_bytes;
}
