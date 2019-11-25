#pragma once

#include <bitset>

#include <QString>
#include <QVector>

class Bitset
{
public:
    Bitset() = default;

    int address() const;

    QString description() const;

    QStringList bitsDescriptions() const;

    std::bitset<8> bits() const;

private:
    int m_address{};
    QString m_description{};
    QStringList m_bitsDescriptions{};
    std::bitset<8> m_bits{};
};
