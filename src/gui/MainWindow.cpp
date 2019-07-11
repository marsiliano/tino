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
        B[i] = new BlockWidget(all[i], this);
        B[i]->setGeometry(0, i, 800, 500);
        this->layout()->addWidget(B[i]);
    }

    btnActivateConnection = new QPushButton(this);
    btnActivateConnection->setText("connect");
    connect(btnActivateConnection, SIGNAL(&QPushButton::clicked), this,
            SLOT(activateConnection()));
    this->layout()->addWidget(btnActivateConnection);

    server = new QModbusRtuSerialSlave(this);
    server->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                   "dev/pts1");
    server->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                   QSerialPort::NoParity);
    server->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                   QSerialPort::Baud57600);
    server->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                   QSerialPort::Data8);
    server->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                   QSerialPort::OneStop);

    QModbusDataUnitMap reg;
    for (int i = 0; i < all.size(); ++i)
        reg.insert(QModbusDataUnit::HoldingRegisters, writeBlock(i));
    server->setMap(reg);
}

void MainWindow::activateConnection()
{
    if (btnActivateConnection->text() == "connect")
        btnActivateConnection->setText("disconect");
    else
        btnActivateConnection->setText("connect");
}

QModbusDataUnit MainWindow::writeBlock(int a)
{
    QVector<quint16> v;

    for (int i = 0; i < all[a].getDim(); ++i) {
        for (int j = 0; j < all[a][i].getDim(); ++j) {
            for (int k = 0; k < all[a][i][j].getDim(); ++k) {
                for (int l = 0; l < 8; ++l) {
                    if (all[a][i][j][l])
                        v.append(1);
                    else
                        v.append(0);
                }
            }
        }
    }
    QModbusDataUnit u(QModbusDataUnit::HoldingRegisters,
                      all[a].getStartAddress(), v);
    return u;
}

MainWindow::~MainWindow()
{
    delete ui;
}

QModbusResponse QModbusServer::processRequest(const QModbusPdu &request)
{
    QModbusResponse response(QModbusResponse::ReadHoldingRegisters,
                             request.data());

    QModbusDataUnit u = writeBlock(request.data().toInt());
    MainWindow::server->setData(u);

    return response;
}
