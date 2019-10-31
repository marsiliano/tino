#pragma once

#include "Flag.hpp"

#include <vector>

class Byte
{
  public:
    bool operator==(const Byte &other) const;

    QString description;
    std::vector<Flag> flags;
};
