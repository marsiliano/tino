#pragma once
#include "Block.hpp"
#include "Settings.hpp"

#include <QDebug>
#include <QModbusRtuSerialMaster>
#include <QModbusRtuSerialSlave>
#include <QtSerialPort/QSerialPort>

class Connector : public QObject
{
    Q_OBJECT
  private:
    QModbusRtuSerialSlave *server;
    std::vector<core::Block> *all;
    QString portname;

  public:
    Connector(std::vector<core::Block> *v, QObject *parent);
    ~Connector();

    bool startConnection(core::Settings s);
    void endConnection();

    int writeBlock(long unsigned int a);
    QString getLinePortText();
    bool isConnected();

  signals:
    void updateBlockReq(long unsigned int);
};
