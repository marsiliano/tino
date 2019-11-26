#pragma once

#include "Byte.hpp"

#include <QPair>

class Word final : public Element
{
  public:
    Word() = default;
    explicit Word(QString descr, int addr);
    explicit Word(QString descr, const QPair<Byte, Byte> &value);
    ~Word() override = default;

    QPair<Byte, Byte> bytes() const;
    void setBytes(const QPair<Byte, Byte> &value);

    int address() const noexcept override;

  private:
    QPair<Byte, Byte> m_bytes{};
};
