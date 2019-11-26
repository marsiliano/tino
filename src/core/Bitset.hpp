#pragma once

#include "Element.hpp"

#include <QVector>
#include <bitset>

class Bitset final : public Element
{
  public:
    Bitset() = default;
    explicit Bitset(QString descr, int addr);
    Bitset(const Bitset &) = default;
    Bitset(Bitset &&)      = default;
    ~Bitset() override     = default;

    Bitset &operator=(const Bitset &) = default;
    Bitset &operator=(Bitset &&) = default;

    void setAt(size_t index, bool value);
    bool valueAt(size_t index) const;

    void setValue(int8_t val) override;
    int value() const override;

    const QStringList &descriptions() const noexcept;
    QStringList &descriptions() noexcept;

    constexpr static size_t size = 8;

  private:
    QStringList m_bitsDescriptions{};
    std::bitset<size> m_bits{};
};
