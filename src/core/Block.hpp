#pragma once

#include "Group.hpp"

namespace core
{
class Block
{
  private:
    std::vector<core::Group> v;
    std::string name;
    int startAddress;

  public:
    Block(std::vector<core::Group> v, int startAddress, std::string name);
    ~Block() {}
    int getStartAddress();
    core::Group &operator[](const int i);
    int getDim();
    std::string getName();
    int getNbyte();
    bool operator==(const Block &other) const;
    Block &operator=(const Block &other);
};

} // namespace core
