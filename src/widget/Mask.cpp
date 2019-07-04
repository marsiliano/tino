#include "Mask.hpp"

#include "../core/Byte.hpp"
#include "QtWidgets/qpushbutton.h"

Mask::Mask(QWidget *parent, ) : QWidget(parent)
{
    QPushButton *b[8];

    for (int i = 0; i < 8; ++i) {
        b[i] = new QPushButton(this);
        b[i]->setGeometry((150 * i), 100, 100, 50);
        connect(b[i], SIGNAL(released()), this, SLOT(doStuff(i)));
    }
}

void Mask::doStuff(int i) {}
