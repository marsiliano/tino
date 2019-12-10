#pragma once

#include <QWidget>
#include <Word.hpp>
#include <memory>

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

    void attachWord(std::shared_ptr<Word> word);

  signals:
    void wordValueChanged(int address);

  private:
    QString m_description{ "" };
    quint16 m_defaultValue{ 0 };
    quint16 m_value{ 0 };
    QLabel *m_decValueLabel{ nullptr };
    QLabel *m_hexValueLabel{ nullptr };
    QSpinBox *m_valueSpinBox{ nullptr };

    std::shared_ptr<Word> m_word;

    void init();
    void checkWidgetSize();
    void update();
};
