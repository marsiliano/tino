#pragma once

#include <QString>

class Byte
{
public:
    Byte() = default;

    int address() const;

    QString description() const;

    int value() const;

private:
    int m_address{};
    QString m_description{};
    int m_value{};
};
