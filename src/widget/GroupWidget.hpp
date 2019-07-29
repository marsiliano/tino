#pragma once
#include "Joined.hpp"
#include "Mask.hpp"

namespace widget
{
class GroupWidget : public QWidget
{
    Q_OBJECT

  public:
    GroupWidget(core::Group *value, QWidget *parent = nullptr);
    GroupWidget(const GroupWidget &) = default;
    ~GroupWidget() override          = default;

  private:
    QBoxLayout *l;
    core::Group *val;

    std::vector<Mask *> m;
    std::vector<Value *> v;
    Joined *jo;
};
} // namespace widget
