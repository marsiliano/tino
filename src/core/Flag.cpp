#include "Flag.hpp"

bool Flag::operator==(const Flag &other) const
{
    return description == other.description && value == other.value &&
           default_value == other.value;
}
