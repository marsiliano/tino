#include "Connector.hpp"

Connector::Connector(core::Block &block)
{
    all.push_back(block);
    modbus_server = nullptr;
    startConnection();

    writeBlock(all[0]);
}

Connector::~Connector()
{
    endConnection();
}

void Connector::startConnection()
{
    //    if (!modbus_server) {
    qDebug() << "is connecting...";

    stocazz *server = new stocazz(all);
    modbus_server   = dynamic_cast<QModbusRtuSerialSlave *>(server);
    if (modbus_server == nullptr) {
        qDebug() << "modbus_server null";
        return;
    }

    QModbusDataUnitMap reg;
    std::for_each(all.begin(), all.end(), [&, this](core::Block &n) {
        reg.insert(QModbusDataUnit::HoldingRegisters,
                   { QModbusDataUnit::HoldingRegisters, 0, n.getNbyte() * 8 });
    });
    modbus_server->setMap(reg);

    modbus_server->setConnectionParameter(
        QModbusDevice::SerialPortNameParameter, "/dev/pts/1");
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

    qDebug() << "error: " << modbus_server->errorString();
    qDebug() << "state: " << modbus_server->state();

    //}
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
    for (int i = 0; i < all.getDim(); ++i) {
        for (int j = 0; j < all[i].getDim(); ++j) {
            int t = 0;
            for (int k = 0; k < 8; ++k) {
                if (all[i][j][k])
                    t += 2 ^ k;
            }
            modbus_server->setData(QModbusDataUnit::HoldingRegisters,
                                   all.getStartAddress() + start++, t);
        }
    }
}

stocazz::stocazz(std::vector<core::Block> &all) : QModbusRtuSerialSlave()
{
    this->all = all;
}

// QModbusResponse stocazz::processRequest(const QModbusPdu &request)
//{
//    QModbusResponse response(QModbusResponse::ReadHoldingRegisters,
//                             request.data());
//    Connector::writeBlock(all[request.data().toInt()]);

//    return response;
//}
