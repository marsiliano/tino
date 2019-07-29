#include "Value.hpp"

widget::Value::Value(core::Byte *value, QWidget *parent) : QWidget(parent)
{
    this->val = value;
    l         = new QBoxLayout(QBoxLayout::LeftToRight, this);
    lblValue =
        new QLabel(QString::fromStdString(val->getName()), this, Qt::Widget);

    box = new QSpinBox(this);
    box->setMinimum(0);
    box->setMaximum(255);

    box->setValue(static_cast<int>(val->getInt()));

    l->addWidget(box, 0, Qt::AlignVCenter);
    l->addWidget(lblValue, 0, Qt::AlignVCenter);

    this->setEnabled(val->getRw());
}
