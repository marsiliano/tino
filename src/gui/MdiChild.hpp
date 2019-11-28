#pragma once

#include <Block.hpp>
#include <QGroupBox>

class MdiChild : public QGroupBox
{
    Q_OBJECT

  public:
    explicit MdiChild(const Block &block, QWidget *parent = nullptr);
};
