#include "Mask.hpp"

widget::Mask::Mask(core::Byte *val, QWidget *parent) : QWidget(parent)
{
    l = new QVBoxLayout(this);
    lblName =
        new QLabel(QString::fromStdString(val->getName()), this, Qt::Widget);
    l->addWidget(lblName, Qt::AlignVCenter);

    for (int i = 0; i < 2; ++i) {
        m.push_back(std::unique_ptr<widget::HalfMask>(
            new widget::HalfMask(val, i * 4, this)));
        l->addWidget(m[i].get(), 0, Qt::AlignVCenter);
    }

    this->setEnabled(val->getWrite());
}

bool widget::Mask::valAt(int i)
{
    return (i < 4 ? m[0]->c->val->operator[](i) : m[1]->c->val->operator[](i));
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
