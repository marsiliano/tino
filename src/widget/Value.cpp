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

    int v = 0;
    for (int i = 0; i < 8; ++i) {
        if (val[i])
            v += pow(2, i);
    }
    std::cout << "value: " << v << std::endl;
    box->setValue(v);

    l->addWidget(lblValue, 0, 0, Qt::AlignVCenter);
    l->addWidget(box, 0, 1, Qt::AlignVCenter);
}
