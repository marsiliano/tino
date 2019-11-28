#pragma once

class Element;

#include <QString>
#include <memory>
#include <vector>

class Block
{
  public:
    bool operator==(const Block &other) const;

    QString description;
    std::vector<std::unique_ptr<Element>> elements;
};
