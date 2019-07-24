#pragma once

#include "Value.hpp"

namespace widget
{
class Joined : public QWidget
{
    Q_OBJECT

  public:
    Joined(core::Group val, QWidget *parent);
    ~Joined() override = default;

  private:
    QBoxLayout *l;
    std::vector<QLabel *> lbl;
};
} // namespace widget
