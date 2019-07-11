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

    btnActivateConnection = new QPushButton();
    btnActivateConnection->setText("connect");
    layout()->addWidget(btnActivateConnection);
    connect(btnActivateConnection, SIGNAL(&QPushButton::clicked), this,
            SLOT(activateConnection()));

    Connector c;
    c.all.push_back(core::Generator::getBlock());

    BlockWidget *B[c.all.size()];
    for (int i = 0; i < c.all.size(); ++i) {
        B[i] = new BlockWidget(c.all[i], this);
        B[i]->setGeometry(0, i, 800, 500);
        this->layout()->addWidget(B[i]);
    }
}

void MainWindow::activateConnection()
{
    if (btnActivateConnection->text() == "connect")
        btnActivateConnection->setText("disconect");
    else
        btnActivateConnection->setText("connect");
}

MainWindow::~MainWindow()
{
    delete ui;
}
