#pragma once

#include "Element.hpp"

class UByte final : public Element
{
  public:
    UByte() = default;
    explicit UByte(QString name, QString descr, int addr);
    explicit UByte(QString name, QString descr, int addr, uint8_t value);
    UByte(const UByte &) = default;
    UByte(UByte &&)      = default;
    ~UByte() override    = default;

    UByte &operator=(const UByte &other) = default;
    UByte &operator=(UByte &&other) = default;

    uint16_t uValue() const override;
    int16_t sValue() const override;

    void setValue(const int16_t value) override;
    void setValue(const uint16_t value) override;

  private:
    uint8_t m_value{};
};

class SByte final : public Element
{
  public:
    SByte() = default;
    explicit SByte(QString name, QString descr, int addr);
    explicit SByte(QString name, QString descr, int addr, int8_t value);
    SByte(const SByte &) = default;
    SByte(SByte &&)      = default;
    ~SByte() override    = default;

    SByte &operator=(const SByte &other) = default;
    SByte &operator=(SByte &&other) = default;

    uint16_t uValue() const override;
    int16_t sValue() const override;

    void setValue(const int16_t value) override;
    void setValue(const uint16_t value) override;

  private:
    int8_t m_value{};
};
