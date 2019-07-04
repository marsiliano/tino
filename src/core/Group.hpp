#include "Byte.hpp"

namespace Core
{
class Group
{
  private:
    Group(std::vector<Byte> v, char type);
    std::vector<Byte> v;
    char type;

  public:
    char getType();
    Byte operator[](const int i);
};
} // namespace Core
