#pragma once
#include "Parser.hpp"

#include <QDebug>
#include <QModbusRtuSerialMaster>
#include <QModbusRtuSerialSlave>
#include <QtSerialPort/QSerialPort>

class Connector : public QObject
{
    Q_OBJECT
  private:
    QModbusRtuSerialSlave *server;
    QString linePortText;
    std::vector<core::Block> *all;

  public:
    Connector(std::vector<core::Block> *v, QObject *parent);
    ~Connector();

    bool startConnection(QString portname, std::string filename);
    void endConnection();

    int writeBlock(long unsigned int a);
    QString getLinePortText();
    bool isConnected();

  signals:
    void updateBlockReq(long unsigned int);
};
