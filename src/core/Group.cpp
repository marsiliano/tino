#include "Group.hpp"

#include "IElement.hpp"

bool Group::operator==(const Group &other) const
{
    return description == other.description && m_elements == other.m_elements;
}
