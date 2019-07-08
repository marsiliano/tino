#include "Mask.hpp"

Mask::Mask(core::Byte val, QWidget *parent) : QWidget(parent)
{
    QGridLayout *l = new QGridLayout(this);

    c      = new BtnContainer();
    c->val = val;

    for (int i = 0; i < 8; ++i) {
        c->b[i] = new QPushButton(this);

        c->b[i]->setGeometry((150 * i), 100, 100, 50);
        c->setClr(i);

        c->b[i]->setText(QString::fromStdString(val.getDescription(i)));

        connect(c->b[i], &QPushButton::clicked, this, [&]() { c->set(i); });

        l->addWidget(c->b[i], 0, i, Qt::AlignVCenter);
    }
}

bool Mask::valAt(const int i)
{
    return c->val[i];
}

QString Mask::getStyleBtn(const int i)
{
    return c->b[i]->styleSheet();
}

void Mask::set(const int i)
{
    c->set(i);
}
