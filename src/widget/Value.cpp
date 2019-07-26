#include "Value.hpp"

widget::Value::Value(core::Byte val, QWidget *parent) : QWidget(parent)
{
    l = new QBoxLayout(QBoxLayout::LeftToRight, this);

    lblValue =
        new QLabel(QString::fromStdString(val.getDesc(0)), this, Qt::Widget);

    box = new QSpinBox(this);
    box->setMinimum(0);
    box->setMaximum(255);

    box->setValue(static_cast<int>(val.getInt()));

    l->addWidget(box, 0, Qt::AlignVCenter);
    l->addWidget(lblValue, 0, Qt::AlignVCenter);

    this->setEnabled(val.getRw());
}
