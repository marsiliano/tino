#include "Joined.hpp"

Joined::Joined(core::Group val, QWidget *parent) : QWidget(parent)
{
    QGridLayout *l = new QGridLayout(this);
    int dim = static_cast<int> (val.getDim());

    QSpinBox *box = new QSpinBox(this);
    box->setMinimum(0);
    box->setMaximum(dim * 255);
    box->setGeometry(0, 0, 150, 100);

    std::vector<QLabel *> lbl;

    long v = 0;
    for (int i = 0; i < dim; ++i) {
        lbl.emplace_back(new QLabel(this, Qt::Widget));
        l->addWidget(lbl[i], i, 0, Qt::AlignVCenter);
        for (int j = 0; j < 8; j++)
            v += (val[i][j] ? pow(2, j) : 0);
    }
    box->setValue(static_cast<int> (v));
    l->addWidget(box, dim, 0, Qt::AlignVCenter);
}
