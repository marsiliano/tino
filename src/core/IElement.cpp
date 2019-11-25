#include "IElement.hpp"

IElement::IElement(QString descr, int addr) :
    m_description{ descr }, m_address{ addr }
{
}

bool IElement::operator==(const IElement &other) const
{
    return description() == other.description() && address() == other.address();
}

bool IElement::operator!=(const IElement &other) const
{
    return !(*this == other);
}

QString IElement::description() const noexcept
{
    return m_description;
}

int IElement::address() const noexcept
{
    return m_address;
}
