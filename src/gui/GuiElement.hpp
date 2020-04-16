#pragma once

#include "../core/Block.hpp"

#include <QWidget>

struct GuiElement
{
    void resetToDefault();

    Element *el;
    std::vector<QWidget *> widgets;
};
