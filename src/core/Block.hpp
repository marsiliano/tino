#include "Group.hpp"

namespace core
{
class Block
{
  private:
    std::vector<core::Group> v;
    std::string name;

  public:
    Block(std::vector<core::Group> v, std::string name);
    core::Group operator[](const int i);
    std::string getName();
};
} // namespace core

/* fare una classe derivata di value, associato o mask?*/
