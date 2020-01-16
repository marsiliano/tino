#pragma once

#include "Byte.hpp"

class UWord final : public Element
{
  public:
    UWord() = default;
    explicit UWord(QString name, QString descr, int addr, int16_t value);
    explicit UWord(QString name, QString descr, int addr, uint8_t low,
                   uint8_t high);
    UWord(const UWord &) = default;
    UWord(UWord &&)      = default;
    ~UWord() override    = default;

    UWord &operator=(const UWord &other) = default;
    UWord &operator=(UWord &&other) = default;

    uint16_t uValue() const override;
    int16_t sValue() const override;

    void setValue(int16_t value) override;
    void setValue(uint16_t value) override;

  private:
    uint16_t m_value;
};

class SWord final : public Element
{
  public:
    SWord() = default;
    explicit SWord(QString name, QString descr, int addr, int16_t value);
    explicit SWord(QString name, QString descr, int addr, uint8_t low,
                   uint8_t high);
    SWord(const SWord &) = default;
    SWord(SWord &&)      = default;
    ~SWord() override    = default;

    SWord &operator=(const SWord &other) = default;
    SWord &operator=(SWord &&other) = default;

    uint16_t uValue() const override;
    int16_t sValue() const override;

    void setValue(int16_t value) override;
    void setValue(uint16_t value) override;

  private:
    int16_t m_value;
};
