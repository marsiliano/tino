#pragma once

#include "../core/Protocol.hpp"
#include "../core/Settings.hpp"

class Configuration
{
public:
    Configuration() = default;
    explicit Configuration(Settings &&set, Protocol &&prot)
        : settings{set}
        , protocol{std::move(prot)}
    {}
    Configuration(const Configuration &) = default;
    Configuration(Configuration &&) = default;
    ~Configuration() = default;

    Configuration &operator=(const Configuration &) = default;
    Configuration &operator=(Configuration &&) = default;

    inline bool operator==(const Configuration &other) const {
        return settings == other.settings && protocol == other.protocol;
    }

    Settings settings;
    Protocol protocol;
};
