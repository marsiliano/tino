#include "Byte.hpp"

core::Byte::Byte(std::vector<bool> v, std::vector<std::string> desc, bool rw)
{
    this->v    = v;
    this->desc = desc;
    this->rw   = rw;
}

std::string core::Byte::getDesc(long unsigned i)
{
    return desc[i];
}
bool core::Byte::operator[](long unsigned i)
{
    return v[i];
}
void core::Byte::set(long unsigned i)
{
    v[i] = !v[i];
}

bool core::Byte::getRw()
{
    return rw;
}
core::Byte &core::Byte::operator=(const core::Byte &other)
{
    this->v    = other.v;
    this->rw   = other.rw;
    this->desc = other.desc;

    return *this;
}

bool core::Byte::operator==(const core::Byte &other) const
{
    if ((rw != other.rw) || (desc.size() != other.desc.size()))
        return false;

    unsigned long i = 0;
    while (i < 8 && v[i] == other.v[i])
        ++i;

    if (i != 8)
        return false;

    i = 0;

    while (i < desc.size() && desc[i] == other.desc[i])
        ++i;

    if (i != desc.size())
        return false;

    return true;
}

bool core::Byte::isMask()
{
    return desc.size() == 1 ? false : true;
}
