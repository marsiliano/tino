#include "Byte.hpp"

core::Byte::Byte(std::vector<bool> v, std::vector<std::string> description,
                 bool rw)
{
    this->v           = v;
    this->description = description;
    this->rw          = rw;
}

std::string core::Byte::getDescription(long unsigned i)
{
    return description[i];
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
    this->v           = other.v;
    this->rw          = other.rw;
    this->description = other.description;

    return *this;
}

bool core::Byte::operator==(const core::Byte &other) const
{
    if ((rw != other.rw) || (description.size() != other.description.size()))
        return false;

    unsigned long i = 0;
    while (i < 8 && v[i] == other.v[i])
        ++i;

    if (i != 8)
        return false;
    i = 0;

    while (i < description.size() && description[i] == other.description[i])
        ++i;

    if (i != description.size())
        return false;

    return true;
}

bool core::Byte::isMask()
{
    return description.size() == 1 ? false : true;
}
