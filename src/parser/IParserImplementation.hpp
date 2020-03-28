#pragma once

#include "Configuration.hpp"

class IParserImplementation {
public:
    virtual ~IParserImplementation() = default;
    virtual Configuration parse(const QString &filename) = 0;
};
