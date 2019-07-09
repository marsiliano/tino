#pragma once
#include "Joined.hpp"
#include "Mask.hpp"
#include "Value.hpp"

#include <QtWidgets/QLabel>

class GroupWidget : public QWidget
{
    Q_OBJECT

  public:
    GroupWidget(core::Group val, QWidget *parent = nullptr);
    ~GroupWidget() override = default;
};
