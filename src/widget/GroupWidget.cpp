#include "GroupWidget.hpp"

GroupWidget::GroupWidget(core::Group val, QWidget *parent) : QWidget(parent)
{
    QGridLayout *l = new QGridLayout(this);
    QLabel *lGroup = new QLabel(this);

    std::vector<Mask*> m;
    std::vector<Value*> v;
    // Joined *j[]

    if (val.getType() == 'm') {
        lGroup->setText(QString::fromStdString("mask group"));
        l->addWidget(lGroup, 0, 0, Qt::AlignVCenter);

        for (int i = 0; i < val.getDim(); ++i) {
            m.emplace_back(new Mask(val[i], this));
            l->addWidget(m[static_cast<unsigned long> (i)], 1 + i, 0, Qt::AlignVCenter);
        }
    } else if (val.getType() == 'v') {
        lGroup->setText(QString::fromStdString("value group"));
        l->addWidget(lGroup, 0, 0, Qt::AlignVCenter);

        for (int i = 0; i < val.getDim(); ++i) {
            v.emplace_back(new Value(val[i], this));
            l->addWidget(v[static_cast<unsigned long> (i)], 1 + i, 0, Qt::AlignVCenter);
        }
    } else if (val.getType() == 'j') {
        lGroup->setText(QString::fromStdString("joined group"));
        l->addWidget(lGroup, 0, 0, Qt::AlignVCenter);

        Joined jo(val, this);
        l->addWidget(&jo, 1, 0, Qt::AlignVCenter);
    }
}
