#include "MainWindow.hpp"

#include "DialogAbout.hpp"
#include "ui_MainWindow.h"

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Tino");

    create_menubar();

    resize(QDesktopWidget().availableGeometry(this).size() * 0.3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::create_menubar()
{
    const auto file = new QMenu("File", ui->menuBar);
    const auto quit = new QAction("Quit", file);
    quit->setShortcut(QKeySequence::StandardKey::Quit);
    connect(quit, &QAction::triggered, this, []() { qApp->quit(); });
    file->addAction(quit);
    ui->menuBar->addMenu(file);

    const auto help  = new QMenu("Help", ui->menuBar);
    const auto about = new QAction("About...", file);
    connect(about, &QAction::triggered, this, [&]() { DialogAbout().exec(); });
    help->addAction(about);
    ui->menuBar->addMenu(help);
}
