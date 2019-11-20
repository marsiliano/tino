#pragma once

#include "Group.hpp"

class Block
{
  public:
    bool operator==(const Block &other) const;

    QString description;
    QVector<Group> groups;
};
