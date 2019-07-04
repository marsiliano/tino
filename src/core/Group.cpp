#include "Group.hpp"

/*m: mask
 * v: value
 * j: joined
 */

Core::Group::Group(std::vector<Core::Byte> v, char type)
{
    this->v    = v;
    this->type = type;
}

char Core::Group::getType()
{
    return type;
}

Core::Byte Core::Group::operator[](const int i)
{
    return v[i];
}
