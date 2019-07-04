#include "MainWindow.hpp"

#include "ui_MainWindow.h"

//#include <yaml-cpp/yaml.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto file = new QMenu("File", ui->menuBar);
    auto quit = new QAction("Quit", file);
    connect(quit, &QAction::triggered, this, []() { qApp->quit(); });
    file->addAction(quit);

    ui->menuBar->addMenu(file);

    m = new Mask(this);
    m->setGeometry(200, 200, 1000, 10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
