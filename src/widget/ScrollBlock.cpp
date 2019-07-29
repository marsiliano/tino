#include "ScrollBlock.hpp"

ScrollBlock::ScrollBlock(core::Block *value, QWidget *parent) : QWidget(parent)
{
    this->val = value;
    l         = new QVBoxLayout(this);

    lBlock = new QLabel(this);
    lBlock->setText(QString::fromStdString(val->getName()));
    lBlock->setMinimumHeight(20);
    lBlock->setStyleSheet("QLabel { background-color: white; color: black; }");

    child = new widget::BlockWidget(val, this);
    child->setMaximumWidth(1000);

    a = new QScrollArea(this);
    a->setWidget(child);

    l->addWidget(lBlock, 0, Qt::AlignHCenter);
    l->addWidget(a);

    this->setMinimumWidth(50);
}
