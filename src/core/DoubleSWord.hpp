#pragma once

#include "Byte.hpp"

class DoubleSWord final : public Element
{
public:
    DoubleSWord() = delete;
    explicit DoubleSWord(QString name, QString descr, uint16_t addr, int32_t value);
    explicit DoubleSWord(QString name, QString descr, uint16_t addr);
    DoubleSWord(const DoubleSWord &) = default;
    DoubleSWord(DoubleSWord &&) = default;
    ~DoubleSWord() override = default;

    DoubleSWord &operator=(const DoubleSWord &other) = default;
    DoubleSWord &operator=(DoubleSWord &&other) = default;

    int32_t dSValue() const override;

    void setValue(int32_t value) override;

private:
    int32_t m_value;
};
