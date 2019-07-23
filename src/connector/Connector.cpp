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
    reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10 });
    reg.insert(QModbusDataUnit::DiscreteInputs,
               { QModbusDataUnit::DiscreteInputs, 0, 999 });
    reg.insert(QModbusDataUnit::InputRegisters,
               { QModbusDataUnit::InputRegisters, 0, 10 });
    reg.insert(QModbusDataUnit::HoldingRegisters,
               { QModbusDataUnit::HoldingRegisters, 0, 10 });

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

void Connector::writeBlock(core::Block &all)
{
    if (modbus_server) {
        int start = 0;
        for (unsigned long i = 0; i < all.getDim(); ++i) {
            for (unsigned long j = 0; j < all[i].getDim(); ++j) {
                int t = 0;

                for (unsigned long k = 0; k < 8; ++k)
                    t += all[i][j][k] ? 2 ^ k : 0;
                if (modbus_server->setData(QModbusDataUnit::HoldingRegisters,
                                           all.getStartAddress() + start++, t))
                    qDebug() << "i can set data";
                else
                    qDebug() << "error writing data: "
                             << modbus_server->errorString();
            }
        }

        //        if (modbus_server->setData(QModbusDataUnit::Coils, 0, true))
        //            qDebug() << "i can set data";
        //        else
        //            qDebug() << "error writing data: " <<
        //            modbus_server->errorString();
    }
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
