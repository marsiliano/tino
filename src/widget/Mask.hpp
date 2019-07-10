#pragma once

#include "BtnContainer.hpp"

class Mask : public QWidget
{
    Q_OBJECT

  public:
    Mask(core::Byte val, QWidget *parent = nullptr);
    ~Mask() {}
    QString getStyleBtn(const int i);
    bool valAt(const int i);

  private:
    BtnContainer *c;

    friend class tst_Mask;
};
