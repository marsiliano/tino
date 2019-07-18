#include "ScrollBlock.hpp"

ScrollBlock::ScrollBlock(core::Block val, QWidget *parent) : QWidget(parent)
{
    l = new QVBoxLayout(this);

    lBlock = new QLabel(this);
    lBlock->setText(QString::fromStdString(val.getName()));
    lBlock->setMinimumHeight(50);
    l->addWidget(lBlock, 0, Qt::AlignLeft);

    child = new BlockWidget(val, this);

    a = new QScrollArea(this);
    a->setWidget(child);
    a->setMaximumWidth(700);
    a->setMinimumWidth(50);

    l->addWidget(a, 0, Qt::AlignLeft);
    this->setMinimumWidth(50);
}
