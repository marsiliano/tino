#pragma once

#include "Flag.hpp"

#include <QVector>

class Byte
{
  public:
    bool operator==(const Byte &other) const;

    QString description;
    QVector<Flag> flags;
};
