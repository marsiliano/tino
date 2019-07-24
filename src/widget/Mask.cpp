#include "Mask.hpp"

widget::Mask::Mask(core::Byte val, QWidget *parent) : QWidget(parent)
{
    l = new QVBoxLayout(this);

    for (int i = 0; i < 2; ++i) {
        m.push_back(new HalfMask(val, i * 4, this));
        l->addWidget(m[i], 0, Qt::AlignVCenter);
    }
}

bool widget::Mask::valAt(int i)
{
    return (i < 4 ? m[0]->c->val[i] : m[1]->c->val[i]);
}

QString widget::Mask::getStyleBtn(int i)
{
    return (i < 4 ? m[0]->c->b[i].first->styleSheet()
                  : m[1]->c->b[i].first->styleSheet());
}

void widget::Mask::clickBtn(int i)
{
    i < 4 ? m[0]->c->b[i].first->click() : m[1]->c->b[i].first->click();
}
