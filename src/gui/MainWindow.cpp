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

    all.push_back(core::Generator::getBlock());

    BlockWidget *B[all.size()];
    for (int i = 0; i < all.size(); ++i) {
        B[i] = new BlockWidget(all[0], this);
        B[i]->setGeometry(0, i, 800, 500);
        this->layout()->addWidget(B[i]);
    }

    btnActivateConnection = new QPushButton(this);
    btnActivateConnection->setText("connect");
    connect(btnActivateConnection, SIGNAL(&QPushButton::clicked), this,
            SLOT(activateConnection()));
    this->layout()->addWidget(btnActivateConnection);

    QModbusServer *server = new QModbusRtuSerialSlave(this);
    QModbusDataUnitMap reg;

    for (int i = 0; i < all.size(); ++i) {
        for (int j = 0; j < all[i].getDim(); ++j) {
            for (int k = 0; k < all[i][j].getDim(); ++k) {
                for (int l = 0; l < all[i][j][k].getDim(); ++l) {
                    QVector<quint16> v;

                    for (int m = 0; m < 8; ++l) {
                        if (all[i][j][l][m])
                            v.append(1);
                        else
                            v.append(0);
                    }
                    QModbusDataUnit u(QModbusDataUnit::DiscreteInputs, 555, v);
                    reg.insert(QModbusDataUnit::DiscreteInputs, u);
                }
            }
        }
    }
    server->setMap(reg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::activateConnection()
{
    if (btnActivateConnection->text() == "connect")
        btnActivateConnection->setText("disconect");
    else
        btnActivateConnection->setText("connect");
}
