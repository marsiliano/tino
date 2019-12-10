#pragma once

#include <QDebug>
#include <QString>

class Element
{
  public:
    Element() = default;
    explicit Element(QString name, QString descr, int addr);
    Element(const Element &) = default;
    Element(Element &&)      = default;
    virtual ~Element()       = default;

    Element &operator=(const Element &) = default;
    Element &operator=(Element &&) = default;

    bool operator==(const Element &other) const;
    bool operator!=(const Element &other) const;

    QString name() const noexcept;
    QString description() const noexcept;
    virtual int address() const noexcept;

    virtual void setValue(int8_t val)  = 0;
    virtual void setValue(int16_t val) = 0;

    virtual int16_t value() const = 0;

  private:
    QString m_name{};
    QString m_description{};
    int m_address{};
};
