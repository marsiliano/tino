#include <iostream>
#include <vector>

class Byte
{
  private:
    std::vector<bool> v;
    std::string name;
    bool rw;
    char type;

  public:
    Byte(std::vector<bool> v, std::string name, bool rw, char type);
    std::string getName()
    {
        return name;
    }
    bool operator[](const int i)
    {
        return v[i];
    }

    bool getRw()
    {
        return rw;
    }
    char getType()
    {
        return type;
    }
};
