#pragma once

#include <QWidget>
#include <memory>

class Word;
class QLabel;
class QSpinBox;

class WordWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit WordWidget(QString description  = QString(),
                        quint16 defaultValue = 0xFFFF,
                        QWidget *parent      = nullptr);

    void updateValue(int16_t val);

    void attachWord(Word *word);

  signals:
    void wordValueChanged(int address);

  private:
    QString m_description{ "" };
    quint16 m_defaultValue{ 0 };
    quint16 m_value{ 0 };
    QLabel *m_decValueLabel{ nullptr };
    QLabel *m_hexValueLabel{ nullptr };
    QSpinBox *m_valueSpinBox{ nullptr };
    Word *m_word{ nullptr };

    void init();
    void checkWidgetSize();
    void update();
};
