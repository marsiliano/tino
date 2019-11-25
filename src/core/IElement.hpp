#pragma once

#include <QString>

class IElement
{
  public:
    IElement() = default;
    explicit IElement(QString descr, int addr);
    IElement(const IElement &) = default;
    IElement(IElement &&)      = default;
    virtual ~IElement();

    IElement &operator=(const IElement &) = default;
    IElement &operator=(IElement &&) = default;

    QString description() const noexcept;
    int address() const noexcept;

  private:
    int m_address{};
    QString m_description{};
};
