#pragma once

#include <QWidget>

class QLabel;
class QSpinBox;

class ByteWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit ByteWidget(QString description = QString(),
                        quint8 defaultValue = 0xFF, QWidget *parent = nullptr);

  private:
    QString m_description{ "" };
    quint8 m_defaultValue{ 0x00 };
    quint8 m_value{ 0x12 };
    QLabel *m_decValueLabel{ nullptr };
    QLabel *m_hexValueLabel{ nullptr };
    QSpinBox *m_valueSpinBox{ nullptr };
    void init();
    void check();
    void update();
};
