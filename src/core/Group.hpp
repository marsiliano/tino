#pragma once

#include "Byte.hpp"

namespace core
{
class Group
{
  private:
    std::vector<Byte> v;
    char type;

  public:
    Group(std::vector<Byte> v, char type);
    Group(std::vector<bool> v, std::vector<std::string> description, bool rw,
          char type);
    ~Group() {}
    void add(std::vector<bool> v, std::vector<std::string> description,
             bool rw);
    char getType();
    Byte &operator[](const int i);
    int getDim();
};
} // namespace core
