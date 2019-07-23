#pragma once
#include "Block.hpp"

#include <QModbusDataUnit>
#include <QModbusRtuSerialSlave>
#include <QModbusServer>
#include <QtSerialPort/QSerialPort>
#include <memory>

// class stocazz : public QModbusRtuSerialSlave
//{
//  private:
//    std::vector<core::Block> all;

//  public:
//    stocazz(std::vector<core::Block> &all);
//    //    QModbusResponse processRequest(const QModbusPdu &request) override;
//};

struct Connector : public QObject {
    QModbusServer *modbus_server{ nullptr };
    Connector(QObject *parent);
    ~Connector();
    void startConnection(QString portname);
    void endConnection();
    void writeBlock(core::Block &block);
};
