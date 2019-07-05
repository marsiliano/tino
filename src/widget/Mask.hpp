#include "../core/Block.hpp"
#include "QtWidgets/qboxlayout.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qwidget.h>

class Mask : public QWidget
{
    Q_OBJECT
  public:
    Mask(core::Byte val, QWidget *parent = nullptr);
    ~Mask() {}
    core::Byte val;
    QPushButton *b[8];
    void setClr(const int i);
  public slots:
    void doStuff(const int i);
};
