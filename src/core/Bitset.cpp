#include "Bitset.hpp"

QStringList Bitset::bitsDescriptions() const
{
    return m_bitsDescriptions;
}

std::bitset<8> Bitset::bits() const
{
    return m_bits;
}
