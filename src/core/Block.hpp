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
    QString category;
    quint16 address;
    std::vector<std::unique_ptr<Element>> elements;
};
