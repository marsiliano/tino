#pragma once

#include "HalfMask.hpp"

class Mask : public QWidget
{
    Q_OBJECT

  public:
    Mask(core::Byte val, QWidget *parent = nullptr);
    ~Mask() override   = default;
    Mask(const Mask &) = default;

    QString getStyleBtn(int i);
    bool valAt(int i);
    void clickBtn(int i);

  private:
    QVBoxLayout *l;
    std::vector<HalfMask *> m;

    friend class tst_Mask;
};
