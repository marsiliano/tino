#include "Mask.hpp"

#include "QtWidgets/qpushbutton.h"

Mask::Mask(core::Byte val, QWidget *parent) : QWidget(parent)
{
    this->val = val;

    QGridLayout *l = new QGridLayout(this);

    for (current = 0; current < 8; ++current) {
        b[current] = new QPushButton(this);

        b[current]->setGeometry((150 * current), 100, 100, 50);
        this->setClr(current);

        b[current]->setText(
            QString::fromStdString(val.getDescription(current)));

        connect(b[current], SIGNAL(clicked()), this, SLOT(doStuff()));

        l->addWidget(b[current], 0, current, Qt::AlignVCenter);
    }
}

void Mask::doStuff()
{
    this->set(current);
}

bool Mask::valAt(const int i)
{
    return val[i];
}

QString Mask::getStyleBtn(const int i)
{
    return b[i]->styleSheet();
}

void Mask::setClr(const int i)
{
    if (this->val[i])
        b[i]->setStyleSheet("background-color:#ff0000;");
    else
        b[i]->setStyleSheet("background-color:#0000ff;");
}

void Mask::set(const int i)
{
    this->val.set(i);
    this->setClr(i);
}
