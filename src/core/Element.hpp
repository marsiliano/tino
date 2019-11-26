#pragma once

#include <QDebug>
#include <QString>

class Element
{
  public:
    Element() = default;
    explicit Element(QString descr, int addr);
    Element(const Element &) = default;
    Element(Element &&)      = default;
    virtual ~Element()       = default;

    Element &operator=(const Element &) = default;
    Element &operator=(Element &&) = default;

    bool operator==(const Element &other) const;
    bool operator!=(const Element &other) const;

    QString description() const noexcept;
    virtual int address() const noexcept;

    virtual void setValue(int8_t val)
    {
        (void)(val);
    }
    virtual void setValue(int16_t val)
    {
        (void)(val);
    }

    virtual int value() const
    {
        return 0;
    }

  private:
    QString m_description{};
    int m_address{};
};
