#pragma once

#include "BtnContainer.hpp"
#include "Value.hpp"

class Joined : public QWidget
{
    Q_OBJECT

  public:
    Joined(core::Group val, QWidget *parent);
};
