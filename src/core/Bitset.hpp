#pragma once

#include "IElement.hpp"

#include <QVector>
#include <bitset>

class Bitset final : public IElement
{
  public:
    QStringList bitsDescriptions() const;

    std::bitset<8> bits() const;

  private:
    QStringList m_bitsDescriptions{};
    std::bitset<8> m_bits{};
};
