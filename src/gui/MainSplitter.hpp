#pragma once
#include "Connector.hpp"
#include "Generator.hpp"
#include "ScrollBlock.hpp"

#include <QFileDialog>
#include <QSplitter>

class MainSplitter : public QWidget
{
  public:
    MainSplitter(const std::vector<core::Block> &blocks, QWidget *parent);
    ~MainSplitter() = default;

  private:
    std::vector<ScrollBlock *> blocksWidget;

    QSplitter *sp;
    std::vector<QSplitter *> spv;

    QVBoxLayout *mainlayout;
};
