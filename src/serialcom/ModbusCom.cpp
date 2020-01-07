#include "ModbusCom.hpp"

#include <Element.hpp>
#include <QDebug>
#include <QModbusRtuSerialSlave>

ModbusCom::ModbusCom(const Protocol &protocol, QObject *parent) :
    QObject(parent), m_protocolRef{ protocol }
{
    m_modbusDevice.reset(new QModbusRtuSerialSlave(this));

    connect(m_modbusDevice.get(), &QModbusServer::errorOccurred, this,
            [this](QModbusDevice::Error error) {
                handleError(m_modbusDevice->errorString(), error);
            });
    connect(m_modbusDevice.get(), &QModbusServer::dataWritten, this,
            &ModbusCom::updateRegisters);

    initializeServer();
}

bool ModbusCom::isConnected() const
{
    return (m_modbusDevice->state() == QModbusDevice::ConnectedState);
}

bool ModbusCom::connectModbus(const Settings &settings)
{
    if (m_modbusDevice->state() == QModbusDevice::ConnectedState) {
        qDebug() << "ModbusCom: Modbus already connected.";
        return false;
    }

    m_modbusDevice->setConnectionParameter(
        QModbusDevice::SerialPortNameParameter, settings.portName);
    m_modbusDevice->setConnectionParameter(
        QModbusDevice::SerialBaudRateParameter, settings.baudRate);
    m_modbusDevice->setConnectionParameter(
        QModbusDevice::SerialDataBitsParameter, settings.dataBits);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                           settings.parity);
    m_modbusDevice->setConnectionParameter(
        QModbusDevice::SerialStopBitsParameter, settings.stopBits);
    m_modbusDevice->setServerAddress(1);

    if (!m_modbusDevice->connectDevice()) {
        qCritical() << "ModbusCom: Modbus connection failed: "
                    << m_modbusDevice->errorString();
        return false;
    }

    qDebug() << "ModbusCom: Modbus connected succesfully.";
    return true;
}

bool ModbusCom::disconnectModbus()
{
    if (m_modbusDevice->state() != QModbusDevice::ConnectedState) {
        qDebug() << "ModbusCom: Modbus not connected.";
        return false;
    }

    m_modbusDevice->disconnectDevice();
    return true;
}

void ModbusCom::writeRegister(int address)
{
    m_modbusDevice->setData(QModbusDataUnit::HoldingRegisters, address,
                            m_protocolRef.elementMap.at(address)->value());
}

void ModbusCom::handleError(const QString &errorString,
                            QModbusDevice::Error error)
{
    if (error == QModbusDevice::NoError || !m_modbusDevice) {
        return;
    }

    qWarning() << QStringLiteral("ModbusCom: Error occurred: %1 (code 0x%2)")
                      .arg(errorString)
                      .arg(error);

    switch (error) {
        case QModbusDevice::NoError:
            break;
        case QModbusDevice::ReadError:
            break;
        case QModbusDevice::WriteError:
            break;
        case QModbusDevice::ConnectionError:
            break;
        case QModbusDevice::ConfigurationError:
            break;
        case QModbusDevice::TimeoutError:
            break;
        case QModbusDevice::ProtocolError:
            break;
        case QModbusDevice::ReplyAbortedError:
            break;
        case QModbusDevice::UnknownError:
            break;
    }
}

void ModbusCom::updateRegisters(QModbusDataUnit::RegisterType table,
                                int address, int size)
{
    for (auto i = 0; i < size; ++i) {
        quint16 value;
        quint16 add = static_cast<quint16>(address + i);

        switch (table) {
            case QModbusDataUnit::HoldingRegisters:
                m_modbusDevice->data(QModbusDataUnit::HoldingRegisters,
                                     static_cast<quint16>(add), &value);
                if (m_protocolRef.elementMap.find(add) !=
                    m_protocolRef.elementMap.end()) {
                    m_protocolRef.elementMap.at(add)->setValue(
                        static_cast<int16_t>(value));
                } else {
                    qWarning()
                        << QStringLiteral("Address %1 is invalid!").arg(add);
                }
                Q_EMIT updateGui(add);
                break;
            default:
                break;
        }
    }
}

bool ModbusCom::initializeServer()
{
    QModbusDataUnitMap reg;
    auto maxAddress = 0;

    for (const auto &el : m_protocolRef.elementMap) {
        if (el.first > maxAddress) {
            maxAddress = el.first;
        }
    }

    reg.insert(QModbusDataUnit::HoldingRegisters,
               { QModbusDataUnit::HoldingRegisters, 0,
                 static_cast<quint16>(maxAddress) });

    return m_modbusDevice->setMap(reg);
}
