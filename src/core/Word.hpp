#pragma once

#include "Byte.hpp"

class Word final : public Element
{
  public:
    Word() = default;
    explicit Word(QString descr, int16_t value);
    explicit Word(QString descr, int addr, uint8_t low, uint8_t high);
    ~Word() override = default;

    Word &operator=(const Word &) = default;
    Word &operator=(Word &&) = default;

    void setValue(int16_t val) override;
    int16_t value() const override;

    uint8_t low() const noexcept;
    uint8_t high() const noexcept;

  private:
    uint8_t m_low{};
    uint8_t m_high{};
};
