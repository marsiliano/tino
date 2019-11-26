#pragma once

#include "Element.hpp"

#include <QVector>
#include <bitset>

class Bitset final : public Element
{
  public:
    Bitset() = default;
    explicit Bitset(QString descr, int addr);
    ~Bitset() override = default;

    QStringList bitsDescriptions{};
    std::bitset<8> bits{};
};
