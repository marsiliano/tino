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

    auto B = new BlockWidget(core::Generator::getBlock(), this);
    B->setGeometry(0, 0, 800, 500);

    this->layout()->addWidget(B);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<core::Block> MainWindow::parse(std::string flname)
{
    std ::vector<core::Block> all;

    return all;
}
