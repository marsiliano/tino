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
    QString getStyleBtn(const int i);
    bool valAt(const int i);
    void set(const int i);
    void clckBtn(const int i);

    friend class tst_Mask;

  private:
    QPushButton *b[8];
    core::Byte val;
    int current;
    void setClr(const int i);
  public slots:
    void doStuff();
};
