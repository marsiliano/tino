#pragma once

#include "Configuration.hpp"
#include "IParserImplementation.hpp"

#include <memory>

class QString;

class ConfigParser
{
public:
    explicit ConfigParser(const QString &filename);

    Configuration parse();

private:
    std::unique_ptr<IParserImplementation> m_impl;
    QString m_filename;
};
