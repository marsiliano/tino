#include "BlockWidget.hpp"

#include <QtWidgets/QLabel>

BlockWidget::BlockWidget(core::Block val, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);

    QLabel *lBlock = new QLabel(this);
    lBlock->setText(QString::fromStdString(val.getName()));
    l->addWidget(lBlock, 0, Qt::AlignHCenter);

    std::vector<GroupWidget *> g;

    for (int i = 0; i < val.getDim(); ++i) {
        g.emplace_back(new GroupWidget(val[i], this));
        l->addWidget(g[static_cast<unsigned long> (i)], 0, Qt::AlignHCenter);
    }
}
