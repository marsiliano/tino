#include "GroupWidget.hpp"

widget::GroupWidget::GroupWidget(core::Group *value, QWidget *parent) :
    QWidget(parent)
{
    this->val = value;
    l         = new QBoxLayout(QBoxLayout::TopToBottom, this);
    long unsigned int i;

    if (val->getType() == 'm') {
        for (i = 0; i < val->getDim(); ++i) {
            m.emplace_back(std::unique_ptr<widget::Mask>(
                new widget::Mask(&(*val)[i], this)));
            l->addWidget(m[static_cast<unsigned long>(i)].get(), 0,
                         Qt::AlignHCenter);
        }
    } else if (val->getType() == 'v') {
        for (i = 0; i < val->getDim(); ++i) {
            v.emplace_back(std::unique_ptr<widget::Value>(
                new widget::Value(&((*val)[i]), this)));
            l->addWidget(v[static_cast<unsigned long>(i)].get(), 0,
                         Qt::AlignHCenter);
        }
    } else if (val->getType() == 'j') {
        jo = std::unique_ptr<widget::Joined>(new widget::Joined(val, this));
        l->addWidget(jo.get(), 0, Qt::AlignHCenter);
    }
}
