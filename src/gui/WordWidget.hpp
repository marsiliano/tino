#pragma once

#include <QWidget>

class QLabel;
class QSpinBox;

class WordWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit WordWidget(QString description  = QString(),
                        quint16 defaultValue = 0xFFFF,
                        QWidget *parent      = nullptr);

  signals:

  public slots:

  private:
    QString m_description{ "" };
    quint16 m_defaultValue{ 0 };
    quint16 m_value{ 0 };
    QLabel *m_decValueLabel{ nullptr };
    QLabel *m_hexValueLabel{ nullptr };
    QSpinBox *m_valueSpinBox{ nullptr };
    void init();
    void check();
    void update();
};
