#include "Connector.hpp"

#include <fstream>

Connector::Connector(std::vector<core::Block> *v, QObject *parent) :
    QObject(parent)
{
    server = new QModbusRtuSerialSlave(this);
    all    = v;

    short unsigned int sz = 0;
    for (core::Block &bl : (*all))
        sz += static_cast<quint16>(bl.getNbyte());

    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::HoldingRegisters,
               { QModbusDataUnit::HoldingRegisters, (*all)[0].getStart(), sz });

    server->setMap(reg);

    connect(server, &QModbusServer::dataWritten, this,
            [this](QModbusDataUnit::RegisterType table, int address, int size) {
                QModbusDataUnit u(table, address, size);
                // unit contains one HoldingRegisters

                if (!server->data(&u))
                    qDebug() << "cannot server->data()";

                long unsigned int i =
                    0; // find in which block data were written
                while ((i < all->size()) &&
                       (*all)[i].getStart() <= u.startAddress())
                    ++i;

                --i;
                qDebug() << "i: " << i << ", value: " << u.value(0)
                         << ", address: " << u.startAddress();
                (*all)[i].setIntAtAddress(u.value(0), u.startAddress());
                emit updateBlockReq(i);
            });
}

Connector::~Connector()
{
    endConnection();

    delete server;
    server = nullptr;
}

bool Connector::startConnection(core::Settings s)
{
    if (server) {
        // set server parameter

        server->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                       QString::fromStdString(s.portName));
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

        qDebug() << "error: " << server->errorString();
        qDebug() << "state: " << server->state();

        return (server->state() == QModbusRtuSerialSlave::ConnectedState);
    } // end if (server && portname.length() > 0)
    return false;
}

void Connector::endConnection()
{
    if (server)
        server->disconnectDevice();
}

int Connector::writeBlock(long unsigned int a)
{
    int cont = -1;
    if (server) {
        ++cont;
        for (unsigned long i = 0; i < (*all)[a].getDim(); ++i) {
            for (unsigned long j = 0; j < (*all)[a][i].getDim(); ++j) {
                if ((*all)[a][i][j].getWrite()) {
                    if (!server->setData(QModbusDataUnit::HoldingRegisters,
                                         (*all)[a].getStart() + cont,
                                         (*all)[a][i][j].getInt()))
                        qDebug() << "error writing data: " << cont << " "
                                 << server->errorString();
                }
                ++cont;
            }
        }
    }
    return cont;
}

bool Connector::isConnected()
{
    return (server->state() == QModbusServer::ConnectedState);
}

std::string Connector::openPort()
{
    system("gnome-terminal -e \'socat -d -d -lf socatOutput.txt pty,raw,echo=0 "
           "pty,raw,echo=0\'");

    std::ifstream socatOutput;
    socatOutput.open("socatOutput.txt");
    std::string ret;
    int pos;

    for (int i = 0; i < 2; ++i) {
        std::string temp;
        getline(socatOutput, temp);
        pos = temp.find("/dev/pts/", 0);

        if (ret.empty())
            ret = temp.substr(pos, 10);
        else {
            std::string notifyText = ("notify-send \"connect your client to " +
                                      temp.substr(pos, 10) + "\"");
            qDebug() << QString::fromStdString(notifyText);
            system(notifyText.c_str());
        }
    }
    return ret;
}

void Connector::closePort()
{
    system("killall socat");
}
