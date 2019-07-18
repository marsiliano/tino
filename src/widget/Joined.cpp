#include "Joined.hpp"

Joined::Joined(core::Group val, QWidget *parent) : QWidget(parent)
{
    l       = new QBoxLayout(QBoxLayout::LeftToRight, this);
    int dim = static_cast<int>(val.getDim());

    QSpinBox *box = new QSpinBox(this);
    box->setMinimum(0);
    box->setMaximum(dim * 255);
    l->addWidget(box, 0, Qt::AlignVCenter);

    std::vector<QLabel *> lbl;

    long v = 0;
    for (int i = 0; i < dim; ++i) {
        lbl.emplace_back(
            new QLabel(QString::fromStdString(val[i].getDescription(0)), this,
                       Qt::Widget));
        l->addWidget(lbl[i], 0, Qt::AlignVCenter);
        for (int j = 0; j < 8; j++)
            v += (val[i][j] ? pow(2, j) : 0);
    }
    box->setValue(static_cast<int>(v));
}
