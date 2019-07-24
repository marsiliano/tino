#include "BlockWidget.hpp"

widget::BlockWidget::BlockWidget(core::Block val, QWidget *parent) :
    QWidget(parent)
{
    l = new QBoxLayout(QBoxLayout::TopToBottom, this);

    for (long unsigned int i = 0; i < val.getDim(); ++i) {
        g.emplace_back(new GroupWidget(val[i], this));
        l->addWidget(g[i], 0, Qt::AlignLeft);
    }

    QSizePolicy policy(QSizePolicy::Maximum, QSizePolicy::Maximum,
                       QSizePolicy::DefaultType);
    this->setSizePolicy(policy);
}
