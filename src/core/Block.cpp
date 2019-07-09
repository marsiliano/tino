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

bool core::Block::operator==(const core::Block &other)
{
    if ((name != other.name) || (v.size() != other.v.size()))
        return false;

    for (int i = 0; i < v.size(); ++i) {
        if (!(v[i] == other.v[i]))
            return false;
    }

    qDebug() << "block";
    return true;
}

core::Block &core::Block::operator=(const core::Block &other)
{
    for (int i = 0; i < other.v.size(); ++i)
        this->v[i] = other.v[i];

    name = other.name;
    return *this;
}
