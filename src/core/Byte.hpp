#pragma once

#include "IElement.hpp"

class Byte final : public IElement
{
  public:
    Byte() = default;
    explicit Byte(QString descr, int addr);
    explicit Byte(QString descr, int addr, int value);
    ~Byte() override = default;

    int value() const;
    void setValue(int value);

  private:
    int m_value{};
};
