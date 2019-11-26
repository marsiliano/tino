#pragma once

#include <Protocol.hpp>

class QDockWidget;
class QStandardItem;

class Element;

class ConfigViewFactory
{
  public:
    QDockWidget *makeConfigView(const Protocol &prot);

  private:
    int m_emptyItemCounter;

    QStandardItem *makeItem(Element *element);
};
