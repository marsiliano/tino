#include "HalfMask.hpp"

widget::HalfMask::HalfMask(core::Byte *value, int offset, QWidget *parent) :
    QWidget(parent)
{
    this->val = value;
    l         = new QHBoxLayout(this);

    c = std::unique_ptr<BtnContainer>(new BtnContainer(val));

    for (int i = offset; i < 4 + offset; ++i) {
        c->setClr(i);

        c->b[i].first->setText(QString::fromStdString(c->val->getDesc(i)));
        connect(c->b[i].first.get(), &QPushButton::clicked, this,
                c->b[i].second);

        l->addWidget(c->b[i].first.get(), 0, Qt::AlignLeft);
    }
}
