#include "Connector.hpp"
#include "MainWindow.hpp"

#include <QApplication>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::vector<core::Block> all;

    BlockWidget *B[all.size()];
    for (int i = 0; i < all.size(); ++i) {
        B[i] = new BlockWidget(all[i], this);
        B[i]->setGeometry(0, i, 800, 500);
        this->layout()->addWidget(B[i]);
    }

    Connector c(all);

    return a.exec();
}
