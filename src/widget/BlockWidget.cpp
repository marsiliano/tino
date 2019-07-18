#include "BlockWidget.hpp"

BlockWidget::BlockWidget(core::Block val, QWidget *parent) : QWidget(parent)
{
    l = new QBoxLayout(QBoxLayout::TopToBottom, this);

    std::vector<GroupWidget *> g;

    for (int i = 0; i < val.getDim(); ++i) {
        g.emplace_back(new GroupWidget(val[i], this));
        l->addWidget(g[static_cast<unsigned long>(i)], 0, Qt::AlignLeft);
    }
}
