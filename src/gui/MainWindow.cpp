#include "MainWindow.hpp"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
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

    // load file
    btnFile = new QPushButton(this);
    btnFile->setText("load file");
    top->addWidget(btnFile, 0, Qt::AlignVCenter);

    connect(btnFile, &QPushButton::clicked, this, [this]() {
        QString filename = QFileDialog::getOpenFileName(
            this, tr("Open config"), "/", tr("json Files (*.json)"));

        //        "/home/fsl/tino/src/conf.json"
        qDebug() << "filename: " << filename;
        blocks = core::Generator::parse(filename.toStdString());

        for (std::vector<core::Block>::size_type i = 0; i < blocks.size();
             ++i) {
            blocksWidget.push_back(new BlockWidget(blocks[i], this));
            blocksWidget[i]->setGeometry(50 + i * blockWidth, 150, blockWidth,
                                         600);
            mainlayout->addWidget(blocksWidget[i], 0, i, Qt::AlignLeft);
            blocksWidget[i]->show();
        }
        c = new Connector(&blocks, this);
    });

    QRect r(50, 50, 400, 100);
    top->setGeometry(r);

    this->layout()->addItem(top);
    this->layout()->addItem(mainlayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
