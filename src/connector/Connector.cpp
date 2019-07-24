#include "Connector.hpp"

Connector::Connector(short unsigned int sz, QObject *parent) : QObject(parent)
{
    modbus_server = new QModbusRtuSerialSlave(this);

    //    QModbusRtuSerialSlave *tmpServer = new QModbusRtuSerialSlave(this);
    //    if (!tmpServer) {
    //        qDebug() << "tmpServer null";
    //        return;
    //    }

    //    modbus_server = dynamic_cast<stocazz *>(tmpServer);
    //    if (!modbus_server) {
    //        qDebug() << "modbus_server null";
    //        return;
    //    }

    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::HoldingRegisters,
               { QModbusDataUnit::HoldingRegisters, 0, sz });

    modbus_server->setMap(reg);
}

Connector::~Connector()
{
    endConnection();

    delete modbus_server;
    modbus_server = nullptr;
}

bool Connector::startConnection(QString portname)
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

        return (modbus_server->state() == QModbusRtuSerialSlave::ConnectedState
                    ? true
                    : false);
    }
    return false;
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
                             << " address: " << (all.getStartAddress() + cont);
                else
                    qDebug() << "error writing data: "
                             << modbus_server->errorString();
            }
        }
    }
    return cont;
}

// stocazz::stocazz(QObject *parent) : QModbusRtuSerialSlave(parent) {}

// QModbusResponse stocazz::processRequest(const QModbusPdu &request)
//{
//    QModbusResponse response(QModbusResponse::ReadHoldingRegisters,
//                             request.data());
//    //    Connector::writeBlock(all[request.data().toInt()]);
//    qDebug() << "this thing actually does something";

//    return response;
//}
