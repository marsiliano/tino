#include "MainWindow.hpp"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    core::Block tblock = core::Generator::getBlock1();
    Connector c(tblock);

    ui->setupUi(this);

    auto file = new QMenu("File", ui->menuBar);
    auto quit = new QAction("Quit", file);
    connect(quit, &QAction::triggered, this, []() { qApp->quit(); });
    file->addAction(quit);

    ui->menuBar->addMenu(file);

    top        = new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainlayout = new QGridLayout(this);

    lblPort = new QLabel(this);
    lblPort->setText("Port: ");
    top->addWidget(lblPort, 0, Qt::AlignVCenter);

    linePort = new QLineEdit(this);
    top->addWidget(linePort, 0, Qt::AlignVCenter);

    btnConnect = new QPushButton(this);
    btnConnect->setText("connect");
    top->addWidget(btnConnect, 0, Qt::AlignVCenter);

    connect(btnConnect, SIGNAL(&QPushButton::clicked), this,
            SLOT(activateConnection()));

    QRect r(50, 50, 400, 100);
    top->setGeometry(r);
    mainlayout->addItem(top, 0, 0, Qt::AlignTop);

    std::vector<BlockWidget *> B;
    for (std::vector<core::Block>::size_type i = 0; i < c.all.size(); ++i) {
        B.push_back(new BlockWidget(c.all[i], this));
        B[i]->setGeometry(50 + i * 500, 150, 800, 400);
        mainlayout->addWidget(B[i], i + 1, 0, Qt::AlignLeft);
    }
    this->layout()->addItem(mainlayout);
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
