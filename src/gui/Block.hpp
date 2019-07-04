#include "Byte.hpp"

#include <map>

class Block
{
  private:
    std::vector<Byte> v;
    std::string name;
    int type;

  public:
    Block(std::vector<Byte> v, std::string name, int type);
    int getType();
    std::map<int, int> m
    {
        return type;
    }
    std::string getName()
    {
        return name;
    }

    Byte operator[](const int i)
    {
        return v[i];
    }
};

/* fare una classe derivata di value, associato o mask?*/
