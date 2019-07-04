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
    void doStuff(int i);
    core::Byte val;
    QPalette getClr(bool state);
};
