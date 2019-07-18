#pragma once
#include "BlockWidget.hpp"

#include <QScrollArea>

class ScrollBlock : public QWidget
{
    Q_OBJECT

  public:
    ScrollBlock(core::Block val, QWidget *parent = nullptr);

  private:
    BlockWidget *child;

    QLabel *lBlock;
    QScrollArea *a;
    QVBoxLayout *l;
};
