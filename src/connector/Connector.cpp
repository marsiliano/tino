#include "Connector.hpp"

Connector::Connector(core::Block &block)
{
    all.push_back(block);
    server = nullptr;
    startConnection();

    QModbusDataUnitMap reg;
    std::for_each(all.begin(), all.end(), [&, this](core::Block &n) {
        reg.insert(QModbusDataUnit::HoldingRegisters, writeBlock(n));
    });

    auto modbus_server = dynamic_cast<QModbusRtuSerialSlave *>(server);
    if (modbus_server == nullptr)
        return;
    modbus_server->setMap(reg);
    QModbusDataUnit u = Connector::writeBlock(all[0]);
    server->setData(u);
}

Connector::~Connector()
{
    endConnection();
}

void Connector::startConnection()
{
    //    if (!server) {
    qDebug() << "is connecting...";
    server = new stocazz(all);
    server->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                   "/dev/pts/1");
    server->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                   QSerialPort::EvenParity);
    server->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                   QSerialPort::Baud57600);
    server->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                   QSerialPort::Data8);
    server->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                   QSerialPort::OneStop);
    server->setServerAddress(1);

    if (!server->connectDevice())
        qDebug() << "cannot connect ";

    qDebug() << "error: " << server->errorString();
    qDebug() << "state: " << server->state();

    //}
}

void Connector::endConnection()
{
    if (server)
        server->disconnectDevice();
    delete server;
    server = nullptr;
}

QModbusDataUnit Connector::writeBlock(core::Block &all)
{
    QVector<quint16> v;

    for (int i = 0; i < all.getDim(); ++i) {
        for (int j = 0; j < all[i].getDim(); ++j) {
            for (int k = 0; k < 8; ++k) {
                if (all[i][j][k])
                    v.append(1);
                else
                    v.append(0);
            }
        }
    }
    QModbusDataUnit u(QModbusDataUnit::HoldingRegisters, all.getStartAddress(),
                      v);
    return u;
}

stocazz::stocazz(std::vector<core::Block> &all) : QModbusRtuSerialSlave()
{
    this->all = all;
}

QModbusResponse stocazz::processRequest(const QModbusPdu &request)
{
    QModbusResponse response(QModbusResponse::ReadHoldingRegisters,
                             request.data());

    QModbusDataUnit u = Connector::writeBlock(all[request.data().toInt()]);
    this->setData(u);

    return response;
}
