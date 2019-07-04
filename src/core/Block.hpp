#include "Group.hpp"

namespace Core
{
class Block
{
  private:
    std::vector<Core::Group> v;
    std::string name;

  public:
    Block(std::vector<Core::Group> v, std::string name);
    Core::Group operator[](const int i);
    std::string getName();
};
} // namespace Core

/* fare una classe derivata di value, associato o mask?*/
