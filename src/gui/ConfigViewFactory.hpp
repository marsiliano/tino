#pragma once

#include <Protocol.hpp>

class QDockWidget;
class QStandardItem;

class ConfigViewFactory
{
  public:
    QDockWidget *makeConfigView(const Protocol &prot);

  private:
    int m_emptyItemCounter;

    template<typename T> QStandardItem *makeItem(T t);
};
