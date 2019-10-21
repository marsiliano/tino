#pragma once

#include <QString>
#include <Settings.hpp>

class ConfigParser
{
  public:
    core::Settings parse(const QString &filename);
};
