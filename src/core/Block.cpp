#include "Block.hpp"

Core::Block::Block(std::vector<Core::Group> v, std::string name)
{
    this->v    = v;
    this->name = name;
}
std::string Core::Block::getName()
{
    return name;
}
Core::Group Core::Block::operator[](const int i)
{
    return v[i];
}
