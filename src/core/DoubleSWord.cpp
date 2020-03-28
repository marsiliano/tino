#include "DoubleSWord.hpp"

DoubleSWord::DoubleSWord(QString name, QString descr, uint16_t addr, int32_t value)
    : Element{std::move(name), std::move(descr), addr}
    , m_value{value}
{
    setType(Element::Type::SWord);
}

DoubleSWord::DoubleSWord(QString name, QString descr, uint16_t addr)
    : Element{std::move(name), std::move(descr), addr}
    , m_value{0}
{
    setType(Element::Type::SWord);
}

int32_t DoubleSWord::dSValue() const
{
    return static_cast<int32_t>(m_value);
}

void DoubleSWord::setValue(int32_t value)
{
    if (valOutOfBound<int64_t, int32_t>(value)) {
        throw std::logic_error("Out of bound value <int64_t, int32_t>");
    }

    m_value = value;
}
