#pragma once

#include "Byte.hpp"

#include <QPair>

class Word
{
public:
    Word() = default;

    QString description() const;

    QPair<Byte, Byte> bytes() const;

private:
    QString m_description{};
    QPair<Byte, Byte> m_bytes{};
};
