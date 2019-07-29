#pragma once

#include "Value.hpp"

namespace widget
{
class Joined : public QWidget
{
    Q_OBJECT

  public:
    Joined(core::Group *val, QWidget *parent);
    ~Joined() override = default;

  private:
    QBoxLayout *l;
    std::vector<QLabel *> lbl;
    core::Group *val;
    QSpinBox *box;

    int dim;
};
} // namespace widget
