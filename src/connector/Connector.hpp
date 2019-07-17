#pragma once
#include "Block.hpp"

#include <QModbusDataUnit>
#include <QModbusRtuSerialSlave>
#include <QModbusServer>
#include <QtSerialPort/QSerialPort>

// class stocazz : public QModbusRtuSerialSlave
//{
//  private:
//    std::vector<core::Block> all;

//  public:
//    stocazz(std::vector<core::Block> &all);
//    //    QModbusResponse processRequest(const QModbusPdu &request) override;
//};

class Connector : public QObject
{
  public:
    QModbusServer *modbus_server;
    Connector(core::Block &block, QObject *parent);
    ~Connector();
    std::vector<core::Block> all;
    void startConnection(QString portname);
    void endConnection();
    void writeBlock(core::Block &block);
};
