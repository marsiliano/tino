#include "MainWindow.hpp"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    // ui
    ui->setupUi(this);
    this->setWindowTitle("Tino");

    // titlebar
    auto file = new QMenu("File", ui->menuBar);
    auto quit = new QAction("Quit", file);
    connect(quit, &QAction::triggered, this, []() { qApp->quit(); });
    file->addAction(quit);
    ui->menuBar->addMenu(file);

    all = new CentralWidget(this);
    this->setCentralWidget(all);
}

MainWindow::~MainWindow()
{
    delete ui;
}
