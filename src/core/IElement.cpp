#include "IElement.hpp"

IElement::IElement(QString descr, int addr) :
    m_description{ descr }, m_address{ addr }
{
}

QString IElement::description() const noexcept
{
    return m_description;
}

int IElement::address() const noexcept
{
    return m_address;
}
