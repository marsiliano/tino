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

  private:
    QString m_description{};
    int m_address{};
};

inline QDebug operator<<(QDebug dbg, const Element &element)
{
    QDebugStateSaver saver(dbg);
    dbg << "element description =" << element.description();
    dbg << "element address =" << element.address();
    return dbg;
}
