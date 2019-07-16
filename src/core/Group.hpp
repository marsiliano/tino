#pragma once

#include "Byte.hpp"

namespace core
{
class Group
{
  private:
    std::vector<Byte> v;
    std::string name;
    char type;

  public:
    Group(std::vector<Byte> v, char type /*, std::string name*/);
    Group(std::vector<bool> v, /*std::tring name,*/
          std::vector<std::string> description, bool rw, char type);
    ~Group() {}
    void add(std::vector<bool> v, std::vector<std::string> description,
             bool rw);
    char getType();
    Byte &operator[](const int i);
    int getDim();
    bool operator==(const Group &other) const;
    Group &operator=(const Group &other);
};

} // namespace core
