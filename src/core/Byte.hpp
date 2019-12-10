#pragma once

#include "Element.hpp"

class Byte final : public Element
{
  public:
    Byte() = default;
    explicit Byte(QString name, QString descr, int addr);
    explicit Byte(QString name, QString descr, int addr, int8_t value);
    Byte(const Byte &) = default;
    Byte(Byte &&)      = default;
    ~Byte() override   = default;

    Byte &operator=(const Byte &) = default;
    Byte &operator=(Byte &&) = default;

    void setValue(int8_t value) override;
    void setValue(int16_t val) override;
    int16_t value() const override;

  private:
    int8_t m_value{};
};
