#pragma once

#include "IElement.hpp"

class Byte final : public IElement
{
  public:
    int value() const;

  private:
    int m_value{};
};
