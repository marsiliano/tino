#include "Byte.hpp"

core::Byte::Byte(std::vector<bool> v, std::vector<std::string> description,
                 bool rw)
{
    this->v           = v;
    this->description = description;
    this->rw          = rw;
}

std::vector<std::string> core::Byte::getDescription()
{
    return description;
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

core::Byte &core::Byte::operator=(const core::Byte &other)
{
    this->v           = other.v;
    this->rw          = other.rw;
    this->description = other.description;
    return *this;
}
