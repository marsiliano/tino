#pragma once

#include "Byte.hpp"

#include <QPair>

class Word final : public IElement
{
  public:
    QPair<Byte, Byte> bytes() const;

  private:
    QPair<Byte, Byte> m_bytes{};
};
