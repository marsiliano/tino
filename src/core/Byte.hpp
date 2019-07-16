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
    ~Byte() {}
    std::string getDescription(const int i);
    bool operator[](int const i);
    bool getRw();
    Byte &operator=(const Byte &other);
    void set(const int i);
    int getDim();
    bool operator==(const Byte &other) const;
    bool isMask();
};

} // namespace core
