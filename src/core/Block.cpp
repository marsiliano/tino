#include "Block.hpp"

core::Block::Block(std::vector<core::Group> v, int startAddress,
                   std::string name)
{
    this->v            = v;
    this->name         = name;
    this->startAddress = startAddress;
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

bool core::Block::operator==(const core::Block &other) const
{
    if ((name != other.name) || (v.size() != other.v.size()))
        return false;

    int i = 0;

    while (i < v.size() && v[i] == other.v[i])
        ++i;

    return i == v.size() ? true : false;
}

core::Block &core::Block::operator=(const core::Block &other)
{
    this->v = other.v;

    name = other.name;
    return *this;
}

int core::Block::getStartAddress()
{
    return startAddress;
}

int core::Block::getNbyte()
{
    int n = 0;

    //    std::for_each(v.begin(), v.end(), [&](int &i) { n += v[i].getDim();
    //    });

    return n;
}
