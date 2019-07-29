#include "MainSplitter.hpp"

MainSplitter::MainSplitter(const std::vector<core::Block> &blocks,
                           QWidget *parent) :
    QWidget(parent)
{
    mainlayout = new QVBoxLayout(this);
    sp         = new QSplitter(Qt::Vertical, this);

    long unsigned int cont, i, j;
    cont = i = j = 0;

    for (i = 0; i < blocks.size(); i++) {
        if (i == 0 || i % 4 == 0) {
            spv.emplace_back(new QSplitter(Qt::Horizontal, this));
            j = 0;
        }

        blocksWidget.push_back(new ScrollBlock(blocks[i], this));
        spv[cont]->addWidget(blocksWidget[i]);
        spv[cont]->setCollapsible(static_cast<int>(j), false);

        if (i == blocks.size() - 1 || i % 4 == 3) {
            sp->addWidget(spv[cont]);
            ++cont;
        }
        mainlayout->addWidget(sp, Qt::AlignLeft);
    }
}

void MainSplitter::updateBlock(long unsigned int i)
{
    qDebug() << "started update";
    blocksWidget[i]->update();
    qDebug() << "updatng " << i;
}
