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

    std::vector<std::unique_ptr<Mask>> m;
    std::vector<std::unique_ptr<Value>> v;
    std::unique_ptr<Joined> jo;
};
} // namespace widget
