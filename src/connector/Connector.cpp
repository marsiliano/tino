#include "Connector.hpp"

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

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
    qDebug() << "env: " << QString::fromStdString(std::getenv("HOME"));
    char outFile[300] = "";
    strcat(outFile, std::getenv("HOME"));
    strcat(outFile, "/.tino/socatOutput.txt");
    qDebug() << "outfile: " << QString::fromStdString(outFile);

    // start socat
    std::thread([outFile]() {
        char rm[100] = "rm ";
        strcat(rm, outFile);
        qDebug() << "rm: " << QString::fromStdString(rm);

        char socat[300] = "socat -d -d -lf ";
        strcat(socat, outFile);
        strcat(socat, " pty,raw,echo=0 pty,raw,echo=0");
        qDebug() << "socat: " << QString::fromStdString(socat);

        system(rm);
        system(socat);
    })
        .detach();

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
            char toWrite[300] = "notify-send \"connect your client to ";
            strcat(toWrite, found.c_str());
            strcat(toWrite, "\"");
            system(toWrite);

            //            char *clientPort = std::getenv("HOME");
            //            strcat(clientPort, "/.tino/clientPort.txt");
            char clientPort[300] = "/home/fsl/.tino/clientPort.txt";

            toWrite[0] = '\0';
            strcat(toWrite, "echo \"");
            strcat(toWrite, found.c_str());
            strcat(toWrite, "\" > ");
            strcat(toWrite, clientPort);
            qDebug() << "write: " << QString::fromStdString(toWrite);
            system(toWrite);
        }
    }
    return ret;
}

void Connector::closePort()
{
    system("killall socat");
}
