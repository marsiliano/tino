#include "GroupWidget.hpp"

widget::GroupWidget::GroupWidget(core::Group val, QWidget *parent) :
    QWidget(parent)
{
    l = new QBoxLayout(QBoxLayout::TopToBottom, this);
    long unsigned int i;

    if (val.getType() == 'm') {
        std::vector<Mask *> m;

        for (i = 0; i < val.getDim(); ++i) {
            m.emplace_back(new Mask(val[i], this));
            l->addWidget(m[static_cast<unsigned long>(i)], 0, Qt::AlignHCenter);
        }
    } else if (val.getType() == 'v') {
        std::vector<Value *> v;

        for (i = 0; i < val.getDim(); ++i) {
            v.emplace_back(new Value(val[i], this));
            l->addWidget(v[static_cast<unsigned long>(i)], 0, Qt::AlignHCenter);
        }
    } else if (val.getType() == 'j') {
        Joined *jo = new Joined(val, this);
        l->addWidget(jo, 0, Qt::AlignHCenter);
    }
}
