#include "Block.hpp"

core::Block::Block(std::vector<core::Group> v, std::string name)
{
    this->v    = v;
    this->name = name;
}
std::string core::Block::getName()
{
    return name;
}
core::Group &core::Block::operator[](const int i)
{
    return v[i];
}

int core::Block::getDim()
{
    return v.size();
}
