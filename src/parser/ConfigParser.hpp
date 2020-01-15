#pragma once

#include <Protocol.hpp>
#include <QString>
#include <Settings.hpp>

class Bitset;
class Byte;
class Word;

class QJsonObject;
class QJsonArray;

class Configuration
{
  public:
    Configuration() = default;
    explicit Configuration(Settings &&set, Protocol &&prot);
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
    struct Tags {
        constexpr static const auto settings     = "Settings";
        constexpr static const auto serialPort   = "SerialPort";
        constexpr static const auto protocol     = "CommunicationProtocol";
        constexpr static const auto blocks       = "Blocks";
        constexpr static const auto groups       = "Groups";
        constexpr static const auto name         = "Name";
        constexpr static const auto description  = "Description";
        constexpr static const auto type         = "Type";
        constexpr static const auto bitset       = "Bitset";
        constexpr static const auto byte         = "Byte";
        constexpr static const auto word         = "Word";
        constexpr static const auto address      = "Address";
        constexpr static const auto category     = "Category";
        constexpr static const auto offset       = "Offset";
        constexpr static const auto bits         = "Bits";
        constexpr static const auto defaultValue = "DefaultValue";
    };

    [[nodiscard]] Settings readSettings(const QJsonObject &obj) const noexcept;
    [[nodiscard]] Protocol readBlocks(const QJsonObject &obj) const noexcept;

    std::unique_ptr<Bitset> makeBitset(const QJsonObject &obj,
                                       const Block &b = Block()) const;
    std::unique_ptr<Byte> makeByte(const QJsonObject &obj,
                                   const Block &b = Block()) const;
    std::unique_ptr<Word> makeWord(const QJsonObject &obj,
                                   const Block &b = Block()) const;
};
