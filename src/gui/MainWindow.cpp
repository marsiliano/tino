#include "MainWindow.hpp"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto file = new QMenu("File", ui->menuBar);
    auto quit = new QAction("Quit", file);
    connect(quit, &QAction::triggered, this, []() { qApp->quit(); });
    file->addAction(quit);

    ui->menuBar->addMenu(file);

    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {
        "prova0", "prova1", "prova2", "prova3",
        "prova4", "prova5", "prova6", "prova7",
    };
    core::Byte b(v, s, false);
    std::vector<core::Byte> vb = { b };

    core::Group g(vb, 'm');

    //    auto m = new Mask(b, this);
    auto G = new GroupWidget(g, this);
    G->setGeometry(50, 50, 300, 100);
    this->layout()->addWidget(G);
}

MainWindow::~MainWindow()
{
    delete ui;
}
