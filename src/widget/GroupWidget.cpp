#include "GroupWidget.hpp"

GroupWidget::GroupWidget(core::Group val, QWidget *parent)
{
    QGridLayout *l = new QGridLayout(this);
    QLabel *lGroup = new QLabel(this);

    Mask *m[val.getDim()];
    /*Value *v[]
     * Joined *j[]*/

    if (val.getType() == 'm') {
        lGroup->setText(QString::fromStdString("mask group"));
        l->addWidget(lGroup, 0, 0, Qt::AlignVCenter);

        for (int i = 0; i < val.getDim(); ++i) {
            m[i] = new Mask(val[i], this);
            l->addWidget(m[i], 1 + i, 0, Qt::AlignVCenter);
        }
    } /*else if (val.getType() == 'v') {
    } else if (val.getType() == 'j') {
    }*/
}
