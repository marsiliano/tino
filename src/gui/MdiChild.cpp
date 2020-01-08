#include "MdiChild.hpp"

#include "ByteWidget.hpp"
#include "Led.hpp"
#include "WordWidget.hpp"

#include <Bitset.hpp>
#include <Byte.hpp>
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <Word.hpp>

MdiChild::MdiChild(const Block &block, QWidget *parent) : QWidget(parent)
{
    setWindowTitle(block.description);
    setLayout(new QGridLayout);

    auto r = 0;
    auto c = 0;

    for (const auto &element : block.elements) {
        auto groupBox = new QGroupBox(this);
        groupBox->setTitle(element->description());
        groupBox->setLayout(new QGridLayout);

        if (auto bitset = dynamic_cast<Bitset *>(element.get())) {
            auto leds = std::vector<QWidget *>();
            for (size_t i = 0; i < Bitset::size; ++i) {
                if (c == 4) {
                    ++r;
                    c = 0;
                }
                ++c;

                auto led = new Led(bitset->names().at(static_cast<int>(i)),
                                   this, QSize(30, 30),
                                   bitset->valueAt(i) ? Led::State::On
                                                      : Led::State::Off);
                led->attachBitset(bitset, i);
                connect(led, &Led::bitsetStateChanged, this,
                        &MdiChild::updateModbus);
                leds.emplace_back(led);

                dynamic_cast<QGridLayout *>(groupBox->layout())
                    ->addWidget(led, r, c);
            }
            m_guiElements.emplace_back(GuiElement{ element.get(), leds });
        }

        if (auto byte = dynamic_cast<Byte *>(element.get())) {
            auto bw = new ByteWidget(byte->name(),
                                     static_cast<quint8>(byte->value()));
            bw->attachByte(byte);
            connect(bw, &ByteWidget::byteValueChanged, this,
                    &MdiChild::updateModbus);
            m_guiElements.emplace_back(GuiElement{ element.get(), { bw } });
            dynamic_cast<QGridLayout *>(groupBox->layout())
                ->addWidget(bw, r, c);
        }

        if (auto word = dynamic_cast<Word *>(element.get())) {
            auto ww = new WordWidget(word->name(), word->value());
            ww->attachWord(word);
            connect(ww, &WordWidget::wordValueChanged, this,
                    &MdiChild::updateModbus);
            m_guiElements.emplace_back(GuiElement{ element.get(), { ww } });
            dynamic_cast<QGridLayout *>(groupBox->layout())
                ->addWidget(ww, r, c);
        }

        layout()->addWidget(groupBox);
    }
}

bool MdiChild::hasElementWithAddress(int address) const
{
    auto it = std::find_if(m_addresses.begin(), m_addresses.end(),
                           [&](const auto &add) { return (add == address); });
    return (it != m_addresses.end());
}

void MdiChild::updateGuiElemets()
{
    for (const auto &guiElement : m_guiElements) {
        if (auto bitset = dynamic_cast<Bitset *>(guiElement.el)) {
            for (size_t i = 0; i < Bitset::size; ++i) {
                if (auto led = dynamic_cast<Led *>(guiElement.w.at(i))) {
                    auto state =
                        bitset->valueAt(i) ? Led::State::On : Led::State::Off;
                    led->setState(state);
                }
            }
            continue;
        }

        if (auto byte = dynamic_cast<Byte *>(guiElement.el)) {
            if (auto bw = dynamic_cast<ByteWidget *>(guiElement.w.front())) {
                bw->updateValue(byte->value());
            }
            continue;
        }

        if (auto word = dynamic_cast<Word *>(guiElement.el)) {
            if (auto ww = dynamic_cast<WordWidget *>(guiElement.w.front())) {
                ww->updateValue(word->value());
            }
            continue;
        }
    }
}
