#include "Bitset.hpp"

int Bitset::address() const
{
    return m_address;
}

QString Bitset::description() const
{
    return m_description;
}

QStringList Bitset::bitsDescriptions() const
{
    return m_bitsDescriptions;
}

std::bitset<8> Bitset::bits() const
{
    return m_bits;
}
