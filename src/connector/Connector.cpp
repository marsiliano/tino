#include "Connector.hpp"

Connector::Connector(core::Block &block, QObject *parent) :
    QObject(parent), modbus_server{ nullptr }
{
    all.push_back(block);
}

Connector::~Connector()
{
    endConnection();
}

void Connector::startConnection(QString portname)
{
    modbus_server = new QModbusRtuSerialSlave(this);

    if (!modbus_server) {
        qDebug() << "modbus_server null";
        return;
    }
    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10 });
    //    std::for_each(all.begin(), all.end(), [&, this](core::Block &n) {
    //        reg.insert(QModbusDataUnit::HoldingRegisters,
    //                   { QModbusDataUnit::HoldingRegisters, 0, n.getNbyte() *
    //                   8 });
    //    });
    //    reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10 });
    //    reg.insert(QModbusDataUnit::DiscreteInputs,
    //               { QModbusDataUnit::DiscreteInputs, 0, 10 });
    //    reg.insert(QModbusDataUnit::InputRegisters,
    //               { QModbusDataUnit::InputRegisters, 0, 10 });
    //    reg.insert(QModbusDataUnit::HoldingRegisters,
    //               { QModbusDataUnit::HoldingRegisters, 0, 10 });

    //    if (modbus_server->setMap(reg))
    //        qDebug() << "set map";
    //    else
    //        qDebug() << "unable to set map";

    modbus_server->setConnectionParameter(
        QModbusDevice::SerialPortNameParameter, portname);
    modbus_server->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                          QSerialPort::EvenParity);
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

    //    writeBlock(all[0]);
    modbus_server->setData(QModbusDataUnit::Coils, 0, true);

    QModbusDataUnit q;
    modbus_server->data(&q);
    auto v = q.values();
    qDebug() << "number of values: " << v.size();

    std::for_each(v.begin(), v.end(), [](quint16 i) { qDebug() << i; });
}

void Connector::endConnection()
{
    if (modbus_server)
        modbus_server->disconnectDevice();

    delete modbus_server;
    modbus_server = nullptr;
}

void Connector::writeBlock(core::Block &all)
{
    int start = 0;
    for (unsigned long i = 0; i < all.getDim(); ++i) {
        for (unsigned long j = 0; j < all[i].getDim(); ++j) {
            int t = 0;
            for (unsigned long k = 0; k < 8; ++k)
                t += all[i][j][k] ? 2 ^ k : 0;
            modbus_server->setData(QModbusDataUnit::HoldingRegisters,
                                   all.getStartAddress() + start++, t);
        }
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
