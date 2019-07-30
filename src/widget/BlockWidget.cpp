#include "BlockWidget.hpp"

widget::BlockWidget::BlockWidget(core::Block *value, QWidget *parent) :
    QWidget(parent)
{
    this->val = value;
    l         = new QBoxLayout(QBoxLayout::TopToBottom, this);

    for (long unsigned int i = 0; i < val->getDim(); ++i) {
        g.emplace_back(std::unique_ptr<widget::GroupWidget>(
            new widget::GroupWidget(&((*val)[i]), this)));
        l->addWidget(g[i].get(), 0, Qt::AlignLeft);
    }

    /*QSizePolicy policy(QSizePolicy::Maximum, QSizePolicy::Maximum,
                       QSizePolicy::DefaultType);
    this->setSizePolicy(policy);*/
}
