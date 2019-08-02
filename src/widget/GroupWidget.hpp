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

    std::vector<std::unique_ptr<widget::Mask>> m;
    std::vector<std::unique_ptr<widget::Value>> v;
    std::unique_ptr<widget::Joined> jo;
};
} // namespace widget
