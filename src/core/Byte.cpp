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
    int i;

    if ((rw != other.rw) || (description.size() != other.description.size()))
        return false;

    for (i = 0; i < 8; ++i) {
        if (v[i] != other.v[i])
            return false;
    }

    for (i = 0; i < description.size(); ++i) {
        if (description[i] != other.description[i])
            return false;
    }

    return true;
}
