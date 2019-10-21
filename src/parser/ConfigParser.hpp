#pragma once

#include <QString>
#include <Settings.hpp>

class QJsonObject;

class ConfigParser
{
  public:
    core::Settings parse(const QString &filename);

  private:
    core::Settings read_settings(const QJsonObject &obj) const noexcept;
};
