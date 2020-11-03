#include "ValueWidget.hpp"

#include "../core/Element.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QtDebug>

ValueWidget::ValueWidget(Element *element, int16_t value, QString description, QWidget *parent)
    : QWidget(parent)
    , m_description{description}
    , m_defaultValue{value}
    , m_value{value}
    , m_element{element}
{
    init();
}

void ValueWidget::updateValueFromCommunication(int16_t val)
{
    m_value = val;
    m_valueSpinBox->disconnect();
    m_valueSpinBox->setValue(m_value);
    connectChangesWithCommunication();
}

void ValueWidget::resetToDefault()
{
    m_value = m_defaultValue;
    m_valueSpinBox->setValue(m_value);
}

void ValueWidget::updateCommunicationForChanged(quint64 v)
{
    m_value = v;
    update();

    if (m_element) {
        switch (m_element->type()) {
        case Element::UWord:
            m_element->setValue(static_cast<quint16>(m_value));
            break;

        case Element::SWord:
            m_element->setValue(static_cast<qint16>(m_value));
            break;

        case Element::UByte:
            m_element->setValue(static_cast<quint16>(m_value));
            break;

        case Element::SByte:
            m_element->setValue(static_cast<qint16>(m_value));
            break;

        default:
            qWarning() << "case not handled";
            break;
        }
        emit valueChanged(m_element->address());
    }
}

void ValueWidget::init()
{
    m_value = m_defaultValue;

    auto layout = new QGridLayout(this);
    m_valueSpinBox = new QSpinBox(this);
    m_valueSpinBox->setValue(m_value);
    m_valueSpinBox->setMinimum(0);
    m_valueSpinBox->setMaximum(0xFFFF);
    m_valueSpinBox->setAlignment(Qt::AlignRight);
    m_decValueLabel = new QLabel(this);
    m_decValueLabel->setAlignment(Qt::AlignRight);
    m_hexValueLabel = new QLabel(this);
    m_hexValueLabel->setAlignment(Qt::AlignRight);
    int index = 0;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_valueSpinBox, 0, index++);
    layout->addWidget(m_decValueLabel, 0, index++);
    layout->addWidget(m_hexValueLabel, 0, index++);
    checkWidgetSize();
    connectChangesWithCommunication();
}

void ValueWidget::connectChangesWithCommunication()
{
    connect(m_valueSpinBox,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            &ValueWidget::updateCommunicationForChanged);
}

void ValueWidget::checkWidgetSize()
{
    setMinimumSize(100, 25);
    update();
}

void ValueWidget::update()
{
    m_decValueLabel->setText(QString("%1").arg(m_value, 0, 10));
    m_hexValueLabel->setText(QString("0x%1").arg(m_value, 4, 16, QChar('0')));
}
