#pragma once

#include "IElement.hpp"

#include <QVector>
#include <bitset>

class Bitset final : public IElement
{
  public:
    explicit Bitset(QString descr, int addr);
    ~Bitset() override = default;

    QStringList bitsDescriptions{};
    std::bitset<8> bits{};
};
