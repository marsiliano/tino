#include "Group.hpp"

bool Group::operator==(const Group &other) const
{
    return description == other.description && bytes == other.bytes;
}
