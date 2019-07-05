#pragma once

#include <iostream>
#include <vector>

namespace core
{
class Byte
{
  private:
    std::vector<bool> v;
    std::vector<std::string> description;
    bool rw;

  public:
    Byte() = default;
    Byte(std::vector<bool> v, std::vector<std::string> description, bool rw);
    std::string getDescription(const int i);
    bool operator[](int const i);
    bool getRw();
    Byte &operator=(const Byte &other);
    void set(const int i);
    int getDim();
};
} // namespace core
