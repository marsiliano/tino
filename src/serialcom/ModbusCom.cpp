#include "ModbusCom.hpp"

#include "../core/Bitset.hpp"
#include "../core/Byte.hpp"
#include "../core/Element.hpp"
#include "../core/Word.hpp"

#include <QModbusRtuSerialSlave>
#include <QtDebug>

ModbusCom::ModbusCom(const Protocol &protocol, QObject *parent)
    : QObject(parent)
    , m_modbusDevice{std::make_unique<QModbusRtuSerialSlave>()}
    , m_protocol{protocol}
{
    connect(m_modbusDevice.get(),
            &QModbusServer::errorOccurred,
            this,
            [this](QModbusDevice::Error error) {
                handleError(m_modbusDevice->errorString(), error);
            });
    connect(m_modbusDevice.get(), &QModbusServer::dataWritten, this, &ModbusCom::updateRegisters);

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

    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                           settings.portName);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                           settings.baudRate);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                           settings.dataBits);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, settings.parity);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                           settings.stopBits);
    m_modbusDevice->setServerAddress(1);

    if (!m_modbusDevice->connectDevice()) {
        qCritical() << "ModbusCom: Modbus connection failed: " << m_modbusDevice->errorString();
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
    if (m_protocol.elementMap.find(address) == m_protocol.elementMap.end()) {
        qWarning() << "Element at" << QString::number(address, 16) << "not found";
        return;
    }

    quint16 value = 0;
    const auto el = m_protocol.elementMap.at(address);
    switch (el->type()) {
    case Element::UByte:
    case Element::SByte:
    case Element::Bitset: {
        auto hi = 0;
        auto lo = 0;
        if (address % 2 == 0) {
            hi = el->uValue();
            if (m_protocol.elementMap.find(address + 1) != m_protocol.elementMap.end()) {
                lo = m_protocol.elementMap.at(address + 1)->uValue();
            }
            value = (hi << 8) | lo;
        } else {
            lo = el->uValue();
            if (m_protocol.elementMap.find(address - 1) != m_protocol.elementMap.end()) {
                hi = m_protocol.elementMap.at(address - 1)->uValue();
            }
            value = (hi << 8) | lo;
            address--;
        }
    } break;

    case Element::UWord:
    case Element::SWord: {
        auto hi = 0;
        auto lo = 0;
        if (address % 2 == 0) {
            hi = el->uValue();
            if (m_protocol.elementMap.find(address + 1) != m_protocol.elementMap.end()) {
                lo = m_protocol.elementMap.at(address + 1)->uValue();
            }
            value = (hi << 8) | lo;
        } else {
            //            lo = el->uValue();
            //            if (m_protocol.elementMap.find(address - 1) != m_protocol.elementMap.end()) {
            //                hi = m_protocol.elementMap.at(address - 1)->uValue();
            //            }
            //            value = (hi << 8) | lo;
            //            address--;
        }
        QString hexvalue = QString("0x%1").arg(address, 4, 16, QLatin1Char('0'));
        qDebug() << "write word" << hexvalue << el->uValue();
    } break;

    default:
        qWarning() << "case non handled";
        break;
    }

    m_modbusDevice->disconnect();
    m_modbusDevice->setData(QModbusDataUnit::HoldingRegisters, address, value);
    connect(m_modbusDevice.get(), &QModbusServer::dataWritten, this, &ModbusCom::updateRegisters);
}

void ModbusCom::handleError(const QString &errorString, QModbusDevice::Error error)
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

void ModbusCom::updateRegisters(QModbusDataUnit::RegisterType table, int address, int size)
{
    qDebug() << "received " << address << size;
    const auto writeLowByte = [this](uint16_t lowAddress, uint16_t value) {
        if (m_protocol.elementMap.find(lowAddress) == m_protocol.elementMap.end()) {
            qWarning() << "Element at" << QString::number(lowAddress, 16) << "not found";
            return;
        }

        const auto el = m_protocol.elementMap.at(lowAddress);

        switch (el->type()) {
        case Element::Type::SByte:
            if (const auto sb = dynamic_cast<SByte *>(el)) {
                sb->setValue(static_cast<int16_t>(value));
                Q_EMIT updateGui(sb->address());
            }
            break;
        case Element::Type::UByte:
            if (const auto ub = dynamic_cast<UByte *>(el)) {
                ub->setValue(static_cast<uint16_t>(value));
                Q_EMIT updateGui(ub->address());
            }
            break;
        case Element::Type::Bitset:
            if (const auto bitset = dynamic_cast<Bitset *>(el)) {
                bitset->setValue(static_cast<uint16_t>(value));
                Q_EMIT updateGui(bitset->address());
            }
            break;
        default:
            break;
        }
    };

    if (table != QModbusDataUnit::HoldingRegisters) {
        return;
    }

    for (auto i = 0; i < size; ++i) {
        const auto valueAddress = address + i;
        uint16_t value;
        m_modbusDevice->data(QModbusDataUnit::HoldingRegisters, valueAddress, &value);

        const auto elementAddress = address + (i * 2);
        qDebug() << QString::number(elementAddress, 16) << QString::number(valueAddress, 16)
                 << value;

        if (m_protocol.elementMap.find(elementAddress) == m_protocol.elementMap.end()) {
            qWarning() << "Element at" << QString::number(elementAddress, 16) << "not found";
            continue;
        }

        const auto el = m_protocol.elementMap.at(elementAddress);

        switch (el->type()) {
        case Element::Type::SWord:
            if (const auto sw = dynamic_cast<SWord *>(el)) {
                sw->setValue(static_cast<int16_t>(value));
                Q_EMIT updateGui(sw->address());
            }
            break;
        case Element::Type::UWord:
            if (const auto uw = dynamic_cast<UWord *>(el)) {
                uw->setValue(static_cast<uint16_t>(value));
                Q_EMIT updateGui(uw->address());
            }
            break;
        case Element::Type::SByte: {
            const auto hi = value >> 8;
            if (const auto sb = dynamic_cast<SByte *>(el)) {
                sb->setValue(static_cast<int16_t>(hi));
                Q_EMIT updateGui(sb->address());
            }
            const auto lo = value & 0xFF;
            writeLowByte(elementAddress + 1, lo);
        } break;
        case Element::Type::UByte: {
            const auto hi = value >> 8;
            if (const auto ub = dynamic_cast<UByte *>(el)) {
                ub->setValue(static_cast<uint16_t>(hi));
                Q_EMIT updateGui(ub->address());
            }
            const auto lo = value & 0xFF;
            writeLowByte(elementAddress + 1, lo);
        } break;
        case Element::Type::Bitset: {
            const auto hi = value >> 8;
            if (const auto bitset = dynamic_cast<Bitset *>(el)) {
                bitset->setValue(static_cast<uint16_t>(hi));
                Q_EMIT updateGui(bitset->address());
            }
            const auto lo = value & 0xFF;
            writeLowByte(elementAddress + 1, lo);
        } break;
        default:
            break;
        }
    }
}

bool ModbusCom::initializeServer()
{
    QModbusDataUnitMap reg;
    auto maxAddress = 0;

    for (const auto &el : m_protocol.elementMap) {
        if (el.first > maxAddress) {
            maxAddress = el.first;
        }
    }

    reg.insert(QModbusDataUnit::HoldingRegisters,
               {QModbusDataUnit::HoldingRegisters, 0, static_cast<quint16>(maxAddress + 1)});

    return m_modbusDevice->setMap(reg);
}
