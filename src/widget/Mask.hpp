#pragma once

#include "BtnContainer.hpp"

class Mask : public QWidget
{
    Q_OBJECT

  public:
    Mask(core::Byte val, QWidget *parent = nullptr);
    ~Mask() override   = default;
    Mask(const Mask &) = default;
    QString getStyleBtn(const int i);
    bool valAt(const int i);

  private:
    QBoxLayout *l;
    std::unique_ptr<BtnContainer> c;

    friend class tst_Mask;
};
