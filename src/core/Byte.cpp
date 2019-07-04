#include "Byte.hpp"

Core::Byte::Byte(std::vector<bool> v, std::string name, bool rw)
{
    this->v    = v;
    this->name = name;
    this->rw   = rw;
}

std::string Core::Byte::getName()
{
    return name;
}
bool Core::Byte::operator[](const int i)
{
    return v[i];
}

bool Core::Byte::getRw()
{
    return rw;
}
