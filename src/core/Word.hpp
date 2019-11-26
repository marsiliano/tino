#pragma once

#include "Byte.hpp"

class Word final : public Element
{
  public:
    Word() = default;
    explicit Word(QString descr, int value);
    explicit Word(QString descr, Byte low, Byte high);
    ~Word() override = default;

    Word &operator=(const Word &) = default;
    Word &operator=(Word &&) = default;

    void setValue(int16_t val) override;
    int value() const override;

    int address() const noexcept override;

  private:
    Byte m_low{};
    Byte m_high{};
};
