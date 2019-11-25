#pragma once

class IElement;

#include <QString>
#include <memory>
#include <vector>

class Block
{
  public:
    bool operator==(const Block &other) const;

    QString description;
    std::vector<std::unique_ptr<IElement>> elements;
};
