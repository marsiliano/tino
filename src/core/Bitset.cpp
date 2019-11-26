#include "Bitset.hpp"

Bitset::Bitset(QString descr, int addr) : Element{ descr, addr } {}

void Bitset::setAt(size_t index, bool value)
{
    m_bits.set(index, value);
}

bool Bitset::valueAt(size_t index) const
{
    return m_bits.test(index);
}

void Bitset::setValue(int8_t val)
{
    for (size_t i = 0; i < m_bits.size(); ++i) {
        m_bits[i] = (val & (1 << i)) != 0;
    }
}

int Bitset::value() const
{
    return static_cast<int>(m_bits.to_ulong());
}

const QStringList &Bitset::descriptions() const noexcept
{
    return m_bitsDescriptions;
}

QStringList &Bitset::descriptions() noexcept
{
    return m_bitsDescriptions;
}

static_assert(Bitset::size == 8, "Is the size of bit changed?");
