#include "QtWidgets/qboxlayout.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qwidget.h>

class Mask : public QWidget
{
    Q_OBJECT

  public:
    Mask(QWidget *parent = 0);
    ~Mask() {}
    void doStuff(int i);
  signals:
};
