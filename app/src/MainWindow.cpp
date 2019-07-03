#include "MainWindow.hpp"

#include "ui_MainWindow.h"

#include <yaml-cpp/yaml.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto file = new QMenu("File", ui->menuBar);
    auto quit = new QAction("Quit", file);
    connect(quit, &QAction::triggered, this, []() { qApp->quit(); });
    file->addAction(quit);

    ui->menuBar->addMenu(file);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readYaml()
{
    YAML::Parser p;
    YAML::Alias("");
    //    YAML::Node config = YAML::Load("prova.yaml");

    /*for (std::size_t i = 0; i < config.size(); i++) {
        std::cout << config[i].as<int>();
    }*/
}
