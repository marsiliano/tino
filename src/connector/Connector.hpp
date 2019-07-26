#pragma once
#include "Parser.hpp"

#include <QDebug>
#include <QModbusRtuSerialMaster>
#include <QModbusRtuSerialSlave>
#include <QtSerialPort/QSerialPort>

// class stocazz : public QModbusRtuSerialSlave
//{
//  public:
//    stocazz(QObject *parent);
//    QModbusResponse processRequest(const QModbusPdu &request) override;
//};

class Connector : public QObject
{
  private:
    QModbusRtuSerialSlave *server;
    QString linePortText;
    std::vector<core::Block> *all;

  public:
    Connector(std::vector<core::Block> *v, QObject *parent);
    ~Connector();

    bool startConnection(QString portname, std::string filename);
    void endConnection();

    int writeBlock(int a);
    QString getLinePortText();

  signals:
    void updateBlockReq(int);
};
