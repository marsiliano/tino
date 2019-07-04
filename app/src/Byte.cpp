#include "Byte.hpp"

Byte::Byte(std::vector<bool> v, std::string name, bool rw)
{
    this->v    = v;
    this->name = name;
    this->rw   = rw;
}
