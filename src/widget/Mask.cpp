#include "Mask.hpp"

Mask::Mask(core::Byte val, QWidget *parent) : QWidget(parent)
{
    l = new QBoxLayout(QBoxLayout::LeftToRight, this);

    c      = std::unique_ptr<BtnContainer>(new BtnContainer);
    c->val = val;
    int i  = 0;

    std::for_each(
        c->b.begin(), c->b.end(),
        [&](std::pair<std::unique_ptr<QPushButton>, std::function<void()>> &n) {
            n.first->setGeometry(i, 0, 100, 50);
            c->setClr(i);

            n.first->setText(QString::fromStdString(c->val.getDesc(i)));

            connect(n.first.get(), &QPushButton::clicked, this, n.second);

            l->addWidget(n.first.get(), 0, Qt::AlignVCenter);
            ++i;
        });
}

bool Mask::valAt(const int i)
{
    return c->val[i];
}

QString Mask::getStyleBtn(const int i)
{
    return c->b[i].first->styleSheet();
}
