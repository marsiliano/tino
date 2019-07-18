#include "MainWindow.hpp"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    // conf parsing
    all = core::Generator::parse("/home/fsl/tino/src/conf.json");
    c   = new Connector(all, this);

    // ui
    ui->setupUi(this);
    this->setWindowTitle("Tino");
    blockWidth = 700;

    // titlebar
    auto file = new QMenu("File", ui->menuBar);
    auto quit = new QAction("Quit", file);
    connect(quit, &QAction::triggered, this, []() { qApp->quit(); });
    file->addAction(quit);
    ui->menuBar->addMenu(file);

    // layout
    top        = new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainlayout = new QGridLayout(this);

    // top
    lblPort = new QLabel(this);
    lblPort->setText("Port: ");
    top->addWidget(lblPort, 0, Qt::AlignVCenter);

    linePort = new QLineEdit(this);
    top->addWidget(linePort, 0, Qt::AlignVCenter);

    btnConnect = new QPushButton(this);
    btnConnect->setText("connect");
    top->addWidget(btnConnect, 0, Qt::AlignVCenter);

    connect(btnConnect, &QPushButton::clicked, this, [&]() {
        if (btnConnect->text() == "connect") {
            btnConnect->setText("disconect");
            c->startConnection(linePort->text());
        } else {
            btnConnect->setText("connect");
            c->endConnection();
        }
    });

    QRect r(50, 50, 400, 100);
    top->setGeometry(r);
    mainlayout->addItem(top, 0, 0, Qt::AlignTop);

    // load blocks
    std::vector<BlockWidget *> B;
    for (std::vector<core::Block>::size_type i = 0; i < c->all.size(); ++i) {
        B.push_back(new BlockWidget(c->all[i], this));
        B[i]->setGeometry(50 + i * blockWidth, 150, blockWidth, 600);
        mainlayout->addWidget(B[i], i + 1, 0, Qt::AlignLeft);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
