#pragma once
#include "BlockWidget.hpp"

#include <QScrollArea>

class ScrollBlock : public QWidget
{
    Q_OBJECT

  public:
    ScrollBlock(core::Block *value, QWidget *parent = nullptr);

  private:
    widget::BlockWidget *child;
    core::Block *val;

    QLabel *lBlock;
    QScrollArea *a;
    QVBoxLayout *l;
};
