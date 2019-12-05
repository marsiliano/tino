#include "Element.hpp"

Element::Element(QString name, QString descr, int addr) :
    m_description{ descr }, m_address{ addr }
{
}

bool Element::operator==(const Element &other) const
{
    return description() == other.description() && address() == other.address();
}

bool Element::operator!=(const Element &other) const
{
    return !(*this == other);
}

QString Element::name() const noexcept
{
    return m_name;
}

QString Element::description() const noexcept
{
    return m_description;
}

int Element::address() const noexcept
{
    return m_address;
}
