#pragma once

#include "Block.hpp"

#include <QDebug>
#include <QWidgetSet>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <memory>

namespace widget
{
struct BtnContainer {
    BtnContainer(core::Byte *val);
    BtnContainer(const BtnContainer &) = default;
    ~BtnContainer()                    = default;

    core::Byte *val;

    std::vector<std::pair<std::unique_ptr<QPushButton>, std::function<void()>>>
        b;

    void setClr(const int i);

    static QString clrOn;
    static QString clrOff;
};
} // namespace widget
