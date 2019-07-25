#include "Connector.hpp"

Connector::Connector(short unsigned int strt, short unsigned int sz,
                     QObject *parent) :
    QObject(parent)
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
    std::cout << "strt: " << strt << std::endl;
    std::cout << "sz: " << sz << std::endl;
    reg.insert(QModbusDataUnit::HoldingRegisters,
               { QModbusDataUnit::HoldingRegisters, strt, sz });

    modbus_server->setMap(reg);
}

Connector::~Connector()
{
    endConnection();

    delete modbus_server;
    modbus_server = nullptr;
}

bool Connector::startConnection(QString portname, std::string filename)
{
    auto s = core::Generator::getSettings(filename);

    if (portname.length() <= 0)
        portname = QString::fromStdString(s.portName);
    //    else take the portname from the textbox

    linePortText = portname;

    if (modbus_server && portname.length() > 0) {
        modbus_server->setConnectionParameter(
            QModbusDevice::SerialPortNameParameter, portname);
        modbus_server->setConnectionParameter(
            QModbusDevice::SerialParityParameter, s.Parity);
        modbus_server->setConnectionParameter(
            QModbusDevice::SerialBaudRateParameter, s.BaudRate);
        modbus_server->setConnectionParameter(
            QModbusDevice::SerialDataBitsParameter, s.DataBits);
        modbus_server->setConnectionParameter(
            QModbusDevice::SerialStopBitsParameter, s.StopBits);
        modbus_server->setServerAddress(s.ServerAddress);

        if (!modbus_server->connectDevice())
            qDebug() << "cannot connect ";
        else
            qDebug() << "connect";

        qDebug() << "error: " << modbus_server->errorString();
        qDebug() << "state: " << modbus_server->state();

        return (modbus_server->state() == QModbusRtuSerialSlave::ConnectedState
                    ? true
                    : false);
    } // end if (modbus_server && portname.length() > 0)
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
                                           all.getStartAddress() + cont,
                                           all[i][j].getInt()))
                    qDebug() << "writing " << all[i][j].getInt()
                             << " address: " << (all.getStartAddress() + cont);
                else
                    qDebug() << "error writing data: " << cont << " "
                             << modbus_server->errorString();
                ++cont;
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
