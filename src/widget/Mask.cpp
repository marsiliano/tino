#include "Mask.hpp"

#include "QtWidgets/qpushbutton.h"

Mask::Mask(core::Byte val, QWidget *parent) : QWidget(parent)
{
    this->val = val;
    QPushButton *b[8];

    QGridLayout *l = new QGridLayout(this);

    for (int i = 0; i < 8; ++i) {
        b[i] = new QPushButton(this);

        b[i]->setGeometry((150 * i), 100, 100, 50);
        connect(b[i], SIGNAL(released()), this, SLOT(doStuff(i)));

        b[i]->setPalette(getClr(val[i]));

        l->addWidget(b[i], 0, i, Qt::AlignVCenter);
    }
}

void Mask::doStuff(int i)
{
    this->setPalette(getClr(!val[i]));
}

QPalette Mask::getClr(bool state)
{
    QPushButton temp;
    QPalette pal = temp.palette();

    if (state)
        pal.setColor(QPalette::Button, QColor(255, 0, 0));
    else
        pal.setColor(QPalette::Button, QColor(0, 0, 255));
    return pal;
}
