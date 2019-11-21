#pragma once

#include <QString>

class Flag
{
  public:
    bool operator==(const Flag &other) const;

    QString description;
    bool value{};
    bool default_value{};
};
