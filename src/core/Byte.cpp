#include "Byte.hpp"

core::Byte::Byte(std::vector<bool> v, std::vector<std::string> description,
                 bool rw)
{
    this->v           = v;
    this->description = description;
    this->rw          = rw;
}

std::string core::Byte::getDescription(const int i)
{
    return description[i];
}
bool core::Byte::operator[](const int i)
{
    return v[i];
}
void core::Byte::set(const int i)
{
    v[i] = !v[i];
}

bool core::Byte::getRw()
{
    return rw;
}
int core::Byte::getDim()
{
    return v.size();
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

    bool r;

    for (int i = 0; i < 8; ++i)
        r = v[i] == other.v[i] ? true : false;
    return r;

    for (int i = 0; i < description.size(); ++i)
        r = description[i] != other.description[i] ? true : false;
    return r;
}
