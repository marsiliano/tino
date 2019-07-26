#include "Connector.hpp"

Connector::Connector(std::vector<core::Block> *v, QObject *parent) :
    QObject(parent)
{
    server = new QModbusRtuSerialSlave(this);
    all    = v;

    short unsigned int sz = 0;
    for (core::Block &bl : (*all))
        sz += static_cast<quint16>(bl.getNbyte());

    //    QModbusRtuSerialSlave *tmpServer = new QModbusRtuSerialSlave(this);
    //    if (!tmpServer) {
    //        qDebug() << "tmpServer null";
    //        return;
    //    }

    //    server = dynamic_cast<stocazz *>(tmpServer);
    //    if (!server) {
    //        qDebug() << "server null";
    //        return;
    //    }

    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::HoldingRegisters,
               { QModbusDataUnit::HoldingRegisters, (*all)[0].getStart(), sz });

    server->setMap(reg);

    connect(server, &QModbusServer::dataWritten, this,
            [this](QModbusDataUnit::RegisterType table, int address, int size) {
                QModbusDataUnit u(table, address, size);

                qDebug() << "data were written: "
                         << "address: " << address << ", size: " << size;

                for (int i = 0; i < u.valueCount(); ++i) {
                    int j = 0;

                    while ((*all)[j].getStart() < u.startAddress())
                        ++j;

                    (*all)[j].setIntAtAddress(u.value(i), u.startAddress() + i);
                    emit updateBlockReq(j);
                }
            });
}

Connector::~Connector()
{
    endConnection();

    delete server;
    server = nullptr;
}

bool Connector::startConnection(QString portname, std::string filename)
{
    auto s = core::Parser::getSettings(filename);

    if (portname.length() <= 0)
        portname = QString::fromStdString(s.portName);
    //    else take the portname from the textbox

    linePortText = portname;

    if (server && portname.length() > 0) {
        // set server parameter
        server->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                       portname);
        server->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                       s.Parity);
        server->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                       s.BaudRate);
        server->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                       s.DataBits);
        server->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                       s.StopBits);
        server->setServerAddress(s.ServerAddress);

        // connect server
        if (!server->connectDevice())
            qDebug() << "cannot connect server";
        else
            qDebug() << "connect server";
        qDebug() << "error: " << server->errorString();
        qDebug() << "state: " << server->state();

        emit updateBlockReq(0);

        return (server->state() == QModbusRtuSerialSlave::ConnectedState);
    } // end if (server && portname.length() > 0)
    return false;
}

void Connector::endConnection()
{
    if (server)
        server->disconnectDevice();
}

int Connector::writeBlock(int a)
{
    int cont = -1;
    if (server) {
        ++cont;
        for (unsigned long i = 0; i < (*all)[a].getDim(); ++i) {
            for (unsigned long j = 0; j < (*all)[a][i].getDim(); ++j) {
                if (server->setData(QModbusDataUnit::HoldingRegisters,
                                    (*all)[a].getStart() + cont,
                                    (*all)[a][i][j].getInt()))
                    qDebug() << "writing " << (*all)[a][i][j].getInt()
                             << " address: " << ((*all)[a].getStart() + cont);
                else
                    qDebug() << "error writing data: " << cont << " "
                             << server->errorString();
                ++cont;
            }
        }
    }
    return cont;
}

QString Connector::getLinePortText()
{
    return linePortText;
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
