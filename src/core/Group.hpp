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
    Group(std::vector<Byte> v, char type);
    ~Group()             = default;
    Group(const Group &) = default;
    void add(std::vector<bool> vect, std::vector<std::string> description,
             bool rw, std::string name);
    char getType();
    Byte &operator[](long unsigned i);
    long unsigned getDim() const;
    bool operator==(const Group &other) const;
    Group &operator=(const Group &other);
};

} // namespace core
