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

    Group &operator=(const Group &other);
    bool operator==(const Group &other) const;
    Byte &operator[](long unsigned i);

    char getType();
    long unsigned getDim() const;
};

} // namespace core
