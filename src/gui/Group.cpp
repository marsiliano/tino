#include "Group.hpp"

/*m: mask
 * v: value
 * j: joined
 */

Group::Group(std : vector<Byte> v, char type)
{
    this->v    = v;
    this->type = type;
}

char getType()
{
    return type;
}
