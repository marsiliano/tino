#pragma once

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
    ~Block() {}
    core::Group &operator[](const int i);
    int getDim();
    std::string getName();
};
} // namespace core
