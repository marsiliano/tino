#include "Block.hpp"

Block::Block(std::vector<byte> v, std::string name, int type)
{
    this->v    = v;
    this->name = name;
    this->type = type;
}
