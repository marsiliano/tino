#pragma once

#include "../core/Block.hpp"
#include "QtWidgets/qboxlayout.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qwidget.h>

class BtnContainer
{
  public:
    BtnContainer();
    std::vector<QPushButton *> b;
    core::Byte val;

    void set(const int i);
    void setClr(const int i);
};
