#pragma once

#include "Block.hpp"

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
    std::vector<std::pair<std::unique_ptr<QPushButton>, std::function<void()>>>
        b;
    core::Byte *val;

    void setClr(const int i);
};
} // namespace widget
