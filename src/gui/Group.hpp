#include "Byte.hpp"

class Group
{
  private:
    std::vector<Byte> v;
    char type;

  public:
    char getType();
    Byte operator[](const int i);
};
