#pragma once

#include "Block.hpp"

class Protocol
{
  public:
    bool operator==(const Protocol &other) const;

    QVector<Block> blocks;
};
