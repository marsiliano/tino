#include "HalfMask.hpp"

widget::HalfMask::HalfMask(core::Byte *val, int offset, QWidget *parent) :
    QWidget(parent)
{
    l = new QHBoxLayout(this);

    c = std::unique_ptr<widget::BtnContainer>(new widget::BtnContainer(val));
    c->val = val;

    for (int i = offset; i < 4 + offset; ++i) {
        c->setClr(i);

        c->b[i].first->setText(QString::fromStdString(c->val->getDesc(i)));
        connect(c->b[i].first.get(), &QPushButton::clicked, this,
                c->b[i].second);

        l->addWidget(c->b[i].first.get(), 0, Qt::AlignLeft);
    }
}
