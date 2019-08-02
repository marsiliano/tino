#pragma once

#include "GroupWidget.hpp"

namespace widget
{
class BlockWidget : public QWidget
{
    Q_OBJECT

  public:
    BlockWidget(core::Block *value, QWidget *parent = nullptr);
    BlockWidget(const BlockWidget &) = default;
    BlockWidget &operator=(const BlockWidget &) = default;
    ~BlockWidget() override                     = default;

  private:
    QBoxLayout *l;

    std::vector<std::unique_ptr<widget::GroupWidget>> g;
};
} // namespace widget
