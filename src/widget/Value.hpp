#pragma once

#include "BtnContainer.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

namespace widget
{
class Value : public QWidget
{
    Q_OBJECT

  public:
    Value(core::Byte *value, QWidget *parent = nullptr);
    ~Value() override = default;

  private:
    QBoxLayout *l;

    core::Byte *val;

    QSpinBox *box;
    QLabel *lblValue;
};
} // namespace widget
