#pragma once

#include <algorithm>
#include <cmath>
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
    bool write;
    int start;
    std::string name;

  public:
    Byte() = default;
    Byte(std::vector<bool> v, std::vector<std::string> desc, bool rw,
         std::string name);
    ~Byte()            = default;
    Byte(const Byte &) = default;

    Byte &operator=(const Byte &other);
    bool operator==(const Byte &other) const;
    bool operator[](long unsigned i);

    std::string getDesc(long unsigned i);
    bool getWrite() const;
    std::string getName() const;
    int getInt();

    void set(long unsigned i);
    void setInt(int n);
};
} // namespace core
