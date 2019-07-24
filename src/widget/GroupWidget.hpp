#pragma once
#include "Joined.hpp"
#include "Mask.hpp"

namespace widget
{
class GroupWidget : public QWidget
{
    Q_OBJECT

  public:
    GroupWidget(core::Group val, QWidget *parent = nullptr);
    GroupWidget(const GroupWidget &) = default;
    ~GroupWidget() override          = default;

  private:
    QBoxLayout *l;
};
} // namespace widget
