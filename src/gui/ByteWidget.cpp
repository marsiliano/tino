#include "ByteWidget.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>

ByteWidget::ByteWidget(QString description, quint8 defaultValue,
                       QWidget *parent) :
    QWidget(parent),
    m_description(std::move(description)), m_defaultValue(defaultValue)
{
    init();
}

void ByteWidget::updateValue(int16_t value)
{
    m_valueSpinBox->setValue(value);
}

void ByteWidget::init()
{
    m_value = m_defaultValue;

    auto layout    = new QGridLayout(this);
    m_valueSpinBox = new QSpinBox(this);
    m_valueSpinBox->setValue(m_value);
    m_valueSpinBox->setMinimum(0);
    m_valueSpinBox->setMaximum(255);
    connect(m_valueSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            [=](int i) {
                m_value = i;
                update();
            });
    m_decValueLabel = new QLabel(this);
    m_hexValueLabel = new QLabel(this);
    int index       = 0;
    layout->addWidget(m_valueSpinBox, 0, index++);
    layout->addWidget(m_decValueLabel, 0, index++);
    layout->addWidget(m_hexValueLabel, 0, index++);
    checkWidgetSize();
}

void ByteWidget::checkWidgetSize()
{
    setMinimumSize(50, 25);
    update();
}

void ByteWidget::update()
{
    m_decValueLabel->setText(QString("%1").arg(m_value, 0, 10));
    m_hexValueLabel->setText(QString("0x%1").arg(m_value, 2, 16, QChar('0')));
}
