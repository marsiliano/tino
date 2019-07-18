#pragma once

#include "BtnContainer.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <cmath>

class Value : public QWidget
{
    Q_OBJECT

  public:
    Value(core::Byte val, QWidget *parent = nullptr);
    ~Value() override = default;

  private:
    QBoxLayout *l;
    QSpinBox *box;
    QLabel *lblValue;
};
