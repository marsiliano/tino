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

    top = new QGridLayout(this);

    lblPort = new QLabel(this);
    lblPort->setText("Port: ");
    top->addWidget(lblPort, 0, 0, Qt::AlignVCenter);

    linePort = new QLineEdit(this);
    top->addWidget(linePort, 0, 1, Qt::AlignVCenter);

    btnConnect = new QPushButton(this);
    btnConnect->setText("connect");
    top->addWidget(btnConnect, 0, 2, Qt::AlignVCenter);

    connect(btnConnect, SIGNAL(&QPushButton::clicked), this,
            SLOT(activateConnection()));

    layout()->addItem(top);
    core::Block tblock = core::Generator::getBlock1();

    Connector c(tblock);

    std::vector<BlockWidget *> B;
    for (std::vector<core::Block>::size_type i = 0; i < c.all.size(); ++i) {
        B.push_back(new BlockWidget(c.all[i], this));
        B[i]->setGeometry(0, i, 800, 500);
        this->layout()->addWidget(B[i]);
    }
}

void MainWindow::activateConnection()
{
    if (btnConnect->text() == "connect")
        btnConnect->setText("disconect");
    else
        btnConnect->setText("connect");
}

MainWindow::~MainWindow()
{
    delete ui;
}
