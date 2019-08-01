#include "Connector.hpp"

#include <fstream>
#include <future>
#include <stdlib.h>
#include <thread>
#include <utility>

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

// void Connector::portOpened(std::promise<bool> &&writePromise) {}

std::string Connector::openPort()
{
    //    std::promise<bool> writePromise;
    //    std::future<bool> result = writePromise.get_future();

    // socat output path
    std::string outFile = std::getenv("HOME");
    outFile += "/.tino/socatOutput.txt";

    // start socat
    std::thread([&outFile]() {
        std::string rm = "rm " + outFile;
        std::string socat =
            "socat -d -d -lf " + outFile + " pty,raw,echo=0 pty,raw,echo=0";

        system(rm.c_str());
        system(socat.c_str());
        qDebug() << "process ended";
    })
        .detach();

    // wait for socat to start
    //    int i = 0;
    //    do {
    //        i = 0;
    //        std::ifstream socatOutputControl;
    //        socatOutputControl.open(outFile, std::ifstream::in);
    //        std::string temp;

    //        while (getline(socatOutputControl, temp)) {
    //            qDebug() << "temp: " << QString::fromStdString(temp);
    //            ++i;
    //        }
    //        qDebug() << "after while, i: " << i;
    //    } while (i < 3);
    system("sleep 5");

    // open socat output
    std::ifstream socatOutput;
    socatOutput.open(outFile, std::ifstream::in);
    std::string ret;
    std::string found;

    // read socat output
    for (int i = 0; i < 2; ++i) {
        std::string temp;
        getline(socatOutput, temp);
        qDebug() << "temp: " << QString::fromStdString(temp);
        found = temp.substr(temp.find("/dev/pts/", 0), 10);

        if (ret.empty())
            ret = found;
        else {
            std::string notifyText =
                ("notify-send \"connect your client to " + found + "\"");
            system(notifyText.c_str());

            std::string toWrite =
                "echo \"" + found + "\" > /home/$(whoami)/.tino/clientPort.txt";
            system(toWrite.c_str());
        }
    }
    return ret;
}

void Connector::closePort()
{
    system("killall socat");
}
