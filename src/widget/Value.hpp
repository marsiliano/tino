#pragma once

#include "BtnContainer.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <cmath>

class Value : public QWidget
{
  public:
    Value(core::Byte val, QWidget *parent = nullptr);
    ~Value() {}
};
