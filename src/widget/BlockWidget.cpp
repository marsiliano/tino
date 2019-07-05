#include "BlockWidget.hpp"

#include <QtWidgets/QLabel>

BlockWidget::BlockWidget(core::Block val, QWidget *parent)
{
    QGridLayout *l = new QGridLayout(this);

    QLabel *lBlock = new QLabel(this);
    lBlock->setText(QString::fromStdString(val.getName()));
    l->addWidget(lBlock, 0, 0, Qt::AlignVCenter);

    GroupWidget *g[val.getDim()];

    for (int i = 0; i < val.getDim(); ++i) {
        g[i] = new GroupWidget(val[i], this);
        l->addWidget(g[i], 0, i, Qt::AlignHCenter);
    }
}
