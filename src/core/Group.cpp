#include "Group.hpp"

/*m: mask
 * v: value
 * j: joined
 */

core::Group::Group(std::vector<core::Byte> v, char type)
{
    this->v    = v;
    this->type = type;
}

core::Group::Group(std::vector<bool> v, std::vector<std::string> description,
                   bool rw, char type)
{
    this->type = type = type;
    this->add(v, description, rw);
}

void core::Group::add(std::vector<bool> v, std::vector<std::string> description,
                      bool rw)
{
    core::Byte tv(v, description, rw);
    this->v[v.size() - 1] = tv;
}

char core::Group::getType()
{
    return type;
}

core::Byte core::Group::operator[](const int i)
{
    return v[i];
}

int core::Group::getDim()
{
    return v.size();
}
