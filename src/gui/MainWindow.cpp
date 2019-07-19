#include "MainWindow.hpp"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    // ui
    ui->setupUi(this);
    this->setWindowTitle("Tino");

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

    // connect
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

    // draw blocks
    connect(btnFile, &QPushButton::clicked, this, [this]() {
        QString filename = QFileDialog::getOpenFileName(
            this, tr("Open config"), "/", tr("json Files (*.json)"));
        blocks = core::Generator::parse(filename.toStdString());

        c  = new Connector(&blocks, this);
        sp = new QSplitter(Qt::Vertical, this);

        int cont = 0;

        for (std::vector<core::Block>::size_type i = 0; i < blocks.size();
             i++) {
            if (i == 0 || i % 4 == 0)
                spv.emplace_back(new QSplitter(Qt::Horizontal, this));

            blocksWidget.push_back(new ScrollBlock(blocks[i], this));
            spv[cont]->addWidget(blocksWidget[i]);
            spv[cont]->setCollapsible(i, false);

            if (i == blocks.size() - 1 || i % 4 == 3) {
                sp->addWidget(spv[cont]);
                ++cont;
            }
        }
        mainlayout->addWidget(sp, 0, 0, Qt::AlignVCenter);
        resizeSp();
        sp->show();
    });
    QRect r(30, 30, 400, 100);
    top->setGeometry(r);

    this->layout()->addItem(top);
    this->layout()->addItem(mainlayout);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    resizeSp();
}

void MainWindow::resizeSp()
{
    if (sp && c)
        sp->setGeometry(30, 130, this->size().width() - 30,
                        this->size().height() - 135);
}

MainWindow::~MainWindow()
{
    delete ui;
}
