#pragma once
#include "BlockWidget.hpp"

#include <QScrollArea>

class ScrollBlock : public QWidget
{
    Q_OBJECT

  public:
    ScrollBlock(core::Block *value, QWidget *parent = nullptr);

  private:
    QVBoxLayout *l;

    core::Block *val;

    widget::BlockWidget *child;

    QLabel *lBlock;
    QScrollArea *a;
};
