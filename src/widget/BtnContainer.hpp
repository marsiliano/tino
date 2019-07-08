#pragma once

#include "../core/Block.hpp"
#include "QtWidgets/qboxlayout.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qwidget.h>
#include <functional>
#include <memory>

// class BitGui
//{
//  public:
//    std::unique_ptr<QPushButton> btn;
//    bool status;

//    void toggle()
//    {
//        status = !status;
//    }
//};

class BtnContainer
{
  public:
    BtnContainer();
    std::vector<std::pair<std::unique_ptr<QPushButton>, std::function<void()>>>
        b;
    core::Byte val;

    void setClr(const int i);
};
