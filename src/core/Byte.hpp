#pragma once

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
    std::vector<std::string> desc;
    bool rw;
    int start;

  public:
    Byte() = default;
    Byte(std::vector<bool> v, std::vector<std::string> desc, bool rw);
    ~Byte()            = default;
    Byte(const Byte &) = default;

    std::string getDesc(long unsigned i);
    bool operator[](long unsigned i);
    bool getRw();
    Byte &operator=(const Byte &other);
    void set(long unsigned i);
    bool operator==(const Byte &other) const;
    bool isMask();
    double getInt();
};
} // namespace core
