#include "Value.hpp"

Value::Value(core::Byte val, QWidget *parent) : QWidget(parent)
{
    QGridLayout *l = new QGridLayout(this);

    QLabel *lblValue = new QLabel(QString::fromStdString(val.getDescription(0)),
                                  this, Qt::Widget);

    QSpinBox *box = new QSpinBox(this);
    box->setMinimum(0);
    box->setMaximum(255);
    box->setGeometry(0, 0, 150, 100);

    double v = 0;
    for (unsigned long i = 0; i < 8; ++i)
        v += (val[i] ? pow(2, i) : 0);
    box->setValue(static_cast<int> (v));

    l->addWidget(lblValue, 0, 0, Qt::AlignVCenter);
    l->addWidget(box, 0, 1, Qt::AlignVCenter);
}
