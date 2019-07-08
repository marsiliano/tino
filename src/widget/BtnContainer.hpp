#pragma once

#include "../core/Block.hpp"

#include <QWidgetSet>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <functional>
#include <memory>

class BtnContainer
{
  public:
    BtnContainer();
    std::vector<std::pair<std::unique_ptr<QPushButton>, std::function<void()>>>
        b;
    core::Byte val;

    void setClr(const int i);
};
