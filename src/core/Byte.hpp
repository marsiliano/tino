#pragma once

#include "Element.hpp"

class Byte final : public Element
{
  public:
    Byte() = default;
    explicit Byte(QString descr, int addr);
    explicit Byte(QString descr, int addr, int8_t value);
    Byte(const Byte &) = default;
    Byte(Byte &&)      = default;
    ~Byte() override   = default;

    Byte &operator=(const Byte &) = default;
    Byte &operator=(Byte &&) = default;

    void setValue(int8_t value);
    int value() const;

  private:
    int8_t m_value{};
};
