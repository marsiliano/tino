#include "GroupWidget.hpp"

GroupWidget::GroupWidget(core::Group val, QWidget *parent)
{
    QGridLayout *l = new QGridLayout(this);
    QLabel *lGroup = new QLabel(this);

    Mask *m[val.getDim()];
    Value *v[val.getDim()];
    // Joined *j[]

    if (val.getType() == 'm') {
        lGroup->setText(QString::fromStdString("mask group"));
        l->addWidget(lGroup, 0, 0, Qt::AlignVCenter);

        for (int i = 0; i < val.getDim(); ++i) {
            m[i] = new Mask(val[i], this);
            l->addWidget(m[i], 1 + i, 0, Qt::AlignVCenter);
        }
    } else if (val.getType() == 'v') {
        lGroup->setText(QString::fromStdString("value group"));
        l->addWidget(lGroup, 0, 0, Qt::AlignVCenter);

        for (int i = 0; i < val.getDim(); ++i) {
            v[i] = new Value(val[i], this);
            l->addWidget(v[i], 1 + i, 0, Qt::AlignVCenter);
        }
    } else if (val.getType() == 'j') {
        lGroup->setText(QString::fromStdString("joined group"));
        l->addWidget(lGroup, 0, 0, Qt::AlignVCenter);

        Joined jo(val, this);
        l->addWidget(jo, 1, 0, this, Qt::AlignVCenter);
    }
}
