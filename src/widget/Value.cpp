#include "Value.hpp"

Value::Value(core::Byte val, QWidget *parent) : QWidget(parent)
{
    l = new QBoxLayout(QBoxLayout::LeftToRight, this);

    lblValue =
        new QLabel(QString::fromStdString(val.getDesc(0)), this, Qt::Widget);

    box = new QSpinBox(this);
    box->setMinimum(0);
    box->setMaximum(255);

    double v = 0;
    for (unsigned long i = 0; i < 8; ++i)
        v += (val[i] ? pow(2, i) : 0);
    box->setValue(static_cast<int>(v));

    l->addWidget(box, 0, Qt::AlignVCenter);
    l->addWidget(lblValue, 0, Qt::AlignVCenter);
}
