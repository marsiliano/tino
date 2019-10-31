#include "Block.hpp"

bool Block::operator==(const Block &other) const
{
    return description == other.description && groups == other.groups;
}
