#pragma once
#include "Block.hpp"

#include <QDebug>
#include <QModbusRtuSerialSlave>
#include <QtSerialPort/QSerialPort>

// class stocazz : public QModbusRtuSerialSlave
//{
//  public:
//    stocazz(QObject *parent);
//    QModbusResponse processRequest(const QModbusPdu &request) override;
//};

struct Connector : public QObject {
    //    stocazz *modbus_server;
    QModbusRtuSerialSlave *modbus_server;
    Connector(short unsigned int sz, QObject *parent);
    ~Connector();
    bool startConnection(QString portname);
    void endConnection();
    int writeBlock(core::Block &block);
};
