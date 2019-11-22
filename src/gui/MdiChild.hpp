#pragma once

#include <Block.hpp>
#include <Group.hpp>
#include <QGroupBox>

class MdiChild : public QGroupBox
{
    Q_OBJECT

  public:
    explicit MdiChild(const Block &block, QWidget *parent = nullptr);
    explicit MdiChild(const Group &group, QWidget *parent = nullptr);
};
