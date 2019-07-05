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

    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = { "prova" };
    core::Byte b(v, s, false);
    Mask d(b, nullptr);
}

MainWindow::~MainWindow()
{
    delete ui;
}
