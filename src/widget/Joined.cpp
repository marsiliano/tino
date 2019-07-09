#include "Joined.hpp"

Joined::Joined(core::Group val, QWidget *parent)
{
    QGridLayout *l = new QGridLayout(this);

    QSpinBox *box = new QSpinBox(this);
    box->setMinimum(0);
    box->setMaximum(val.getDim() * 255);
    box->setGeometry(0, 0, 150, 100);

    QLabel *lbl[val.getDim()];

    int v = 0;
    for (int i = 0; i < val.getDim(); ++i) {
        lbl[i] = new QLabel(this, Qt::Widget);
        l->addWidget(lbl[i], i, 0, this, Qt::AlignVCenter);
        for (int j = 0; j < 8; j++) {
            if (val[i][j])
                v += pow(2, j);
        }
    }
    box->setValue(v);
    l->addWidget(box, val.getDim(), 0, Qt::AlignVCenter);
}
