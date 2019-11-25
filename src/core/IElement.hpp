#pragma once

#include <QString>

class IElement
{
  public:
    IElement() = default;
    explicit IElement(QString descr, int addr);
    IElement(const IElement &) = default;
    IElement(IElement &&)      = default;
    virtual ~IElement()        = default;

    IElement &operator=(const IElement &) = default;
    IElement &operator=(IElement &&) = default;

    bool operator==(const IElement &other) const;
    bool operator!=(const IElement &other) const;

    QString description() const noexcept;
    int address() const noexcept;

  private:
    QString m_description{};
    int m_address{};
};
