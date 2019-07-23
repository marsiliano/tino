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
               { QModbusDataUnit::DiscreteInputs, 0, 10 });
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

        //    QModbusDataUnit q;
        //    modbus_server->data(&q);
        //    auto values = q.values();
        //    qDebug() << "number of values: " << values.size();

        //    std::for_each(values.begin(), values.end(),
        //                  [](quint16 i) { qDebug() << i; });
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
        //    int start = 0;
        //    for (unsigned long i = 0; i < all.getDim(); ++i) {
        //        for (unsigned long j = 0; j < all[i].getDim(); ++j) {
        //            int t = 0;
        //            for (unsigned long k = 0; k < 8; ++k)
        //                t += all[i][j][k] ? 2 ^ k : 0;
        //            modbus_server->setData(QModbusDataUnit::HoldingRegisters,
        //                                   all.getStartAddress() + start++,
        //                                   t);
        //        }
        //    }

        //    QVector<qint16> v = { 1 };
        //    QModbusDataUnit u(QModbusDataUnit::Coils, 00000, 4);

        if (modbus_server->setData(QModbusDataUnit::Coils, 0, true))
            qDebug() << "i can set data";
        else
            qDebug() << "error writing data: " << modbus_server->errorString();
        //    modbus_server->setData(QModbusDataUnit::Coils, 00001, 1);
        //    modbus_server->setData(QModbusDataUnit::Coils, 00002, 1);
        //    modbus_server->setData(QModbusDataUnit::Coils, 00003, 1);
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
