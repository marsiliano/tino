#pragma once

#include "Byte.hpp"

class Word final : public Element
{
  public:
    Word() = default;
    explicit Word(QString name, QString descr, int addr, int16_t value);
    explicit Word(QString name, QString descr, int addr, uint8_t low,
                  uint8_t high);
    Word(const Word &) = default;
    Word(Word &&)      = default;
    ~Word() override   = default;

    Word &operator=(const Word &) = default;
    Word &operator=(Word &&) = default;

    void setValue(int8_t val) override;
    void setValue(int16_t value) override;
    int16_t value() const override;

    uint8_t low() const noexcept;
    uint8_t high() const noexcept;

  private:
    uint8_t m_low{};
    uint8_t m_high{};
};