#pragma once

#include <QDebug>
#include <algorithm>
#include <functional>
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
    int start;

  public:
    Byte() = default;
    Byte(std::vector<bool> v, std::vector<std::string> description, bool rw);
    ~Byte() = default;
    Byte(const Byte&) = default;

    std::string getDescription(long unsigned i);
    bool operator[](long unsigned i);
    bool getRw();
    Byte &operator=(const Byte &other);
    void set(long unsigned i);
    bool operator==(const Byte &other) const;
    bool isMask();
};

} // namespace core
