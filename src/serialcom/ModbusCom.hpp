#pragma once

#include <Protocol.hpp>
#include <QModbusServer>
#include <QObject>
#include <Settings.hpp>
#include <memory>

class ModbusCom : public QObject
{
    Q_OBJECT
  public:
    explicit ModbusCom(QObject *parent = nullptr);

    bool initializeServer(std::shared_ptr<Protocol> protocol);

    bool isConnected() const;
    bool connectModbus(const Settings &settings);
    bool disconnectModbus();

    void writeRegister(int address);

  signals:
    void updateGui(int address);

  private slots:
    void handleError(const QString &errorString, QModbusDevice::Error error);
    void updateRegisters(QModbusDataUnit::RegisterType table, int address,
                         int size);

  private:
    std::unique_ptr<QModbusServer> m_modbusDevice;
    std::shared_ptr<Protocol> m_protocolRef;
};
