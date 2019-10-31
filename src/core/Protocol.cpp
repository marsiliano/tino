#include "Protocol.hpp"

bool Protocol::operator==(const Protocol &other) const
{
    return blocks == other.blocks;
}
