#include "MainWindow.hpp"

#include "ui_MainWindow.h"

#include <QDesktopWidget>

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

    auto settings = new QMenu("Settings", ui->menuBar);
    auto modbus   = new QAction("Modbus", settings);
    settings->addAction(modbus);
    ui->menuBar->addMenu(settings);

    auto help = new QMenu("Help", ui->menuBar);
    //    auto help = new QAction("Help", help);
    //    help->addAction(help);
    ui->menuBar->addMenu(help);

    all = new CentralWidget(this);
    this->setCentralWidget(all);

    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

MainWindow::~MainWindow()
{
    delete ui;
}
