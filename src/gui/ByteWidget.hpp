#pragma once

#include <Byte.hpp>
#include <QWidget>
#include <memory>

class QLabel;
class QSpinBox;

class ByteWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit ByteWidget(QString description = QString(),
                        quint8 defaultValue = 0xFF, QWidget *parent = nullptr);

    void updateValue(int16_t value);

    void attachByte(std::shared_ptr<Byte> byte);

  signals:
    void byteValueChanged(int address);

  private:
    QString m_description{ "" };
    quint8 m_defaultValue{ 0x00 };
    quint8 m_value{ 0x12 };
    QLabel *m_decValueLabel{ nullptr };
    QLabel *m_hexValueLabel{ nullptr };
    QSpinBox *m_valueSpinBox{ nullptr };
    std::shared_ptr<Byte> m_byte;

    void init();
    void checkWidgetSize();
    void update();
};
