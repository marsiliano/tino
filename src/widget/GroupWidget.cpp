#include "GroupWidget.hpp"

widget::GroupWidget::GroupWidget(core::Group val, QWidget *parent) :
    QWidget(parent)
{
    l        = new QBoxLayout(QBoxLayout::TopToBottom, this);
    lblGroup = new QLabel(this);
    long unsigned int i;

    if (val.getType() == 'm') {
        lblGroup->setText(QString::fromStdString("mask group"));
        l->addWidget(lblGroup, 0, Qt::AlignHCenter);
        std::vector<Mask *> m;

        for (i = 0; i < val.getDim(); ++i) {
            m.emplace_back(new Mask(val[i], this));
            l->addWidget(m[static_cast<unsigned long>(i)], 0, Qt::AlignHCenter);
        }
    } else if (val.getType() == 'v') {
        lblGroup->setText(QString::fromStdString("value group"));
        l->addWidget(lblGroup, 0, Qt::AlignHCenter);
        std::vector<Value *> v;

        for (i = 0; i < val.getDim(); ++i) {
            v.emplace_back(new Value(val[i], this));
            l->addWidget(v[static_cast<unsigned long>(i)], 0, Qt::AlignHCenter);
        }
    } else if (val.getType() == 'j') {
        lblGroup->setText(QString::fromStdString("joined group"));
        l->addWidget(lblGroup, 0, Qt::AlignHCenter);

        Joined *jo = new Joined(val, this);
        l->addWidget(jo, 0, Qt::AlignHCenter);
    }
}
