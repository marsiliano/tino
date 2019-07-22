#include "ScrollBlock.hpp"

ScrollBlock::ScrollBlock(core::Block val, QWidget *parent) : QWidget(parent)
{
    l = new QVBoxLayout(this);

    lBlock = new QLabel(this);
    lBlock->setText(QString::fromStdString(val.getName()));
    lBlock->setMinimumHeight(20);
    lBlock->setStyleSheet("QLabel { background-color: white; color: black; }");

    child = new BlockWidget(val, this);
    child->setMaximumWidth(1000);

    a = new QScrollArea(this);
    a->setWidget(child);

    l->addWidget(lBlock, 0, Qt::AlignHCenter);
    l->addWidget(a);

    this->setMinimumWidth(50);
}
