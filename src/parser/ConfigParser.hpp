#pragma once

#include <Protocol.hpp>
#include <QString>
#include <Settings.hpp>

class QJsonObject;
class QJsonArray;

class Configuration
{
  public:
    explicit Configuration(Settings &&set, Protocol &&prot) :
        settings{ set }, protocol{ prot }
    {
    }
    Configuration()                      = default;
    Configuration(const Configuration &) = default;
    Configuration(Configuration &&)      = default;
    ~Configuration()                     = default;

    Configuration &operator=(const Configuration &) = default;
    Configuration &operator=(Configuration &&) = default;

    bool operator==(const Configuration &other) const;

    Settings settings;
    Protocol protocol;
};

class ConfigParser
{
  public:
    Configuration parse(const QString &filename);

  private:
    Settings read_settings(const QJsonObject &obj) const noexcept;
    Protocol read_blocks(const QJsonArray &array) const noexcept;
};
