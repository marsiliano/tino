#pragma once

#include "Block.hpp"

class Protocol
{
  public:
    bool operator==(const Protocol &other) const;

    std::vector<Block> blocks;
};
