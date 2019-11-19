#pragma once

#include <Protocol.hpp>

class QDockWidget;

class ConfigViewFactory
{
  public:
    QDockWidget *makeConfigView(const Protocol &prot) const;
};
