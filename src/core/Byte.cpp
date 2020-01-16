#include "Byte.hpp"

UByte::UByte(QString name, QString descr, int addr) :
    Element{ std::move(name), std::move(descr), addr }
{
}

UByte::UByte(QString name, QString descr, int addr, uint8_t value) :
    Element{ std::move(name), std::move(descr), addr }, m_value{ value }
{
}

uint16_t UByte::uValue() const
{
    return static_cast<uint16_t>(m_value);
}

int16_t UByte::sValue() const
{
    return static_cast<int16_t>(m_value);
}

void UByte::setValue(const int16_t value)
{
    if (valOutOfBound<int16_t, uint8_t>(value)) {
        throw std::logic_error("Out of bound value <int16_t, uint8_t>");
    }

    m_value = static_cast<uint8_t>(value);
}

void UByte::setValue(const uint16_t value)
{
    if (valOutOfBound<uint16_t, uint8_t>(value)) {
        throw std::logic_error("Out of bound value <uint16_t, uint8_t>");
    }

    m_value = static_cast<uint8_t>(value);
}

SByte::SByte(QString name, QString descr, int addr) :
    Element{ std::move(name), std::move(descr), addr }
{
}

SByte::SByte(QString name, QString descr, int addr, int8_t value) :
    Element{ std::move(name), std::move(descr), addr }, m_value{ value }
{
}

uint16_t SByte::uValue() const
{
    return static_cast<uint16_t>(m_value);
}

int16_t SByte::sValue() const
{
    return static_cast<int16_t>(m_value);
}

void SByte::setValue(const int16_t value)
{
    if (valOutOfBound<int16_t, uint8_t>(value)) {
        throw std::logic_error("Out of bound value <int16_t, uint8_t>");
    }

    m_value = static_cast<int8_t>(value);
}

void SByte::setValue(const uint16_t value)
{
    if (valOutOfBound<uint16_t, uint8_t>(value)) {
        throw std::logic_error("Out of bound value <uint16_t, uint8_t>");
    }

    m_value = static_cast<int8_t>(value);
}
