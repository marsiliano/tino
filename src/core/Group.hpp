#pragma once

#include <QVector>

class IElement;

class Group
{
  public:
    bool operator==(const Group &other) const;

    QString description;
    QVector<IElement *> m_elements;
};
