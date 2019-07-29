#pragma once
#include "Connector.hpp"
#include "ScrollBlock.hpp"

#include <QFileDialog>
#include <QSplitter>

class MainSplitter : public QWidget
{
  public:
    MainSplitter(std::vector<core::Block> *blocks, QWidget *parent);
    ~MainSplitter() = default;
    void updateBlock(long unsigned int i);

  private:
    std::vector<ScrollBlock *> blocksWidget;

    QSplitter *sp;
    std::vector<QSplitter *> spv;

    QVBoxLayout *mainlayout;
    std::vector<core::Block> *blocks;
};
