#include <iostream>
#include <vector>

namespace Core
{
class Byte
{
  private:
    std::vector<bool> v;
    std::string name;
    bool rw;

  public:
    Byte(std::vector<bool> v, std::string name, bool rw);
    std::string getName();
    bool operator[](int const i);
    bool getRw();
};
} // namespace Core
