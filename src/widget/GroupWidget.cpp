#include "GroupWidget.hpp"

widget::GroupWidget::GroupWidget(core::Group *value, QWidget *parent) :
    QWidget(parent)
{
    this->val = value;
    l         = new QBoxLayout(QBoxLayout::TopToBottom, this);
    long unsigned int i;

    if (val->getType() == 'm') {
        for (i = 0; i < val->getDim(); ++i) {
            m.emplace_back(new Mask(&(*val)[i], this));
            l->addWidget(m[static_cast<unsigned long>(i)], 0, Qt::AlignHCenter);
        }
    } else if (val->getType() == 'v') {
        for (i = 0; i < val->getDim(); ++i) {
            v.emplace_back(new Value(&((*val)[i]), this));
            l->addWidget(v[static_cast<unsigned long>(i)], 0, Qt::AlignHCenter);
        }
    } else if (val->getType() == 'j') {
        jo = new Joined(val, this);
        l->addWidget(jo, 0, Qt::AlignHCenter);
    }
}
