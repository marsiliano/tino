#include "Mask.hpp"

#include "QtWidgets/qpushbutton.h"

Mask::Mask(core::Byte val, QWidget *parent) : QWidget(parent)
{
    this->val = val;

    QGridLayout *l = new QGridLayout(this);

    for (int i = 0; i < 8; ++i) {
        b[i] = new QPushButton(this);

        b[i]->setGeometry((150 * i), 100, 100, 50);
        setClr(i);

        connect(b[i], SIGNAL(released()), this, SLOT(doStuff(i)));

        l->addWidget(b[i], 0, i, Qt::AlignVCenter);
    }
}

void Mask::doStuff(const int i)
{
    this->val.set(i);
    setClr(i);
}

void Mask::setClr(const int i)
{
    if (this->val[i])
        b[i]->setStyleSheet("background-color:#ff0000;");
    else
        b[i]->setStyleSheet("background-color:#0000ff;");
}
