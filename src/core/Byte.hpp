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
    std::string name;

  public:
    Byte() = default;
    Byte(std::vector<bool> v, std::vector<std::string> desc, bool rw,
         std::string name);
    ~Byte()            = default;
    Byte(const Byte &) = default;

    std::string getDesc(long unsigned i);
    bool operator[](long unsigned i);
    bool getBitAt(long unsigned i);
    bool getRw();
    std::string getName();
    Byte &operator=(const Byte &other);
    void set(long unsigned i);
    bool operator==(const Byte &other) const;
    bool isMask();
    int getInt();
    void setInt(int n);
};
} // namespace core
