#pragma once

#include "Byte.hpp"

#include <QString>

class Group
{
  public:
    bool operator==(const Group &other) const;

    QString description;
    std::vector<Byte> bytes;
};
