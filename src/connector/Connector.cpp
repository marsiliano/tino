#include "Connector.hpp"

Connector::Connector(QObject *parent) :
    QObject(parent), modbus_server{ nullptr }
{
    modbus_server = new QModbusRtuSerialSlave(this);

    if (!modbus_server) {
        qDebug() << "modbus_server null";
        return;
    }

    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::HoldingRegisters,
               { QModbusDataUnit::HoldingRegisters, 0, 9999 });

    modbus_server->setMap(reg);
}

Connector::~Connector()
{
    endConnection();

    delete modbus_server;
    modbus_server = nullptr;
}

void Connector::startConnection(QString portname)
{
    if (modbus_server) {
        modbus_server->setConnectionParameter(
            QModbusDevice::SerialPortNameParameter, portname);
        modbus_server->setConnectionParameter(
            QModbusDevice::SerialParityParameter, QSerialPort::EvenParity);
        modbus_server->setConnectionParameter(
            QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud57600);
        modbus_server->setConnectionParameter(
            QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        modbus_server->setConnectionParameter(
            QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        modbus_server->setServerAddress(1);

        if (!modbus_server->connectDevice())
            qDebug() << "cannot connect ";
        else
            qDebug() << "connect";

        qDebug() << "error: " << modbus_server->errorString();
        qDebug() << "state: " << modbus_server->state();
    }
}

void Connector::endConnection()
{
    if (modbus_server)
        modbus_server->disconnectDevice();
}

int Connector::writeBlock(core::Block &all)
{
    int cont = -1;
    if (modbus_server) {
        ++cont;
        for (unsigned long i = 0; i < all.getDim(); ++i) {
            for (unsigned long j = 0; j < all[i].getDim(); ++j) {
                if (modbus_server->setData(QModbusDataUnit::HoldingRegisters,
                                           all.getStartAddress() + cont++,
                                           all[i][j].getInt()))
                    qDebug() << "writing " << all[i][j].getInt()
                             << " address: " << (all.getStartAddress() + j);
                else
                    qDebug() << "error writing data: "
                             << modbus_server->errorString();
            }
        }
    }
    return cont;
}

// stocazz::stocazz(std::vector<core::Block> &all) : QModbusRtuSerialSlave()
//{
//    this->all = all;
//}

// QModbusResponse stocazz::processRequest(const QModbusPdu &request)
//{
//    QModbusResponse response(QModbusResponse::ReadHoldingRegisters,
//                             request.data());
//    Connector::writeBlock(all[request.data().toInt()]);

//    return response;
//}
