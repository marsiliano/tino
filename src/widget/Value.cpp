#include "Value.hpp"

Value::Value(core::Byte val, QWidget *parent)
{
    QGridLayout *l = new QGridLayout(this);

    QLabel *lblValue = new QLabel(QString::fromStdString(val.getDescription(0)),
                                  this, Qt::Widget);

    QSpinBox *box = new QSpinBox(this);
    box->setMinimum(0);
    box->setMaximum(255);
    box->setGeometry(0, 0, 150, 100);

    double v = 0;
    for (double i = 0; i < 8; ++i) {
        if (val[i])
            v += pow(10, i);
    }
    box->setValue((int)v);

    l->addWidget(lblValue, 0, 0, Qt::AlignHCenter);
    l->addWidget(box, 1, 0, Qt::AlignHCenter);
}
