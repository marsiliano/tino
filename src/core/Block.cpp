#include "Block.hpp"

#include <IElement.hpp>

bool Block::operator==(const Block &other) const
{
    auto d    = description == other.description;
    auto size = elements.size() == other.elements.size();
    if (!d || !size) {
        return false;
    }

    for (size_t i = 0; i < elements.size(); ++i) {
        if (*elements.at(i) != *other.elements.at(i)) {
            return false;
        }
    }

    return true;
}
