#include "Byte.hpp"

bool Byte::operator==(const Byte &other) const
{
    return description == other.description && flags == other.flags;
}
