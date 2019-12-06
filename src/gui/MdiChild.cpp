#include "MdiChild.hpp"

#include "ByteWidget.hpp"
#include "Led.hpp"
#include "WordWidget.hpp"

#include <Bitset.hpp>
#include <Byte.hpp>
#include <QGridLayout>
#include <Word.hpp>

MdiChild::MdiChild(const Block &block, QWidget *parent) : QGroupBox(parent)
{
    setTitle(block.description);
    auto blockLayout = new QGridLayout(this);
    auto r           = 0;
    auto c           = 0;

    for (const auto &element : block.elements) {
        auto groupBox       = new QGroupBox(this);
        auto groupBoxLayout = new QGridLayout(groupBox);
        groupBox->setLayout(groupBoxLayout);
        groupBox->setTitle(element->description());

        if (auto bitset = dynamic_cast<Bitset *>(element.get())) {
            for (size_t i = 0; i < Bitset::size; ++i) {
                if (c == 4) {
                    ++r;
                    c = 0;
                }
                auto led = new Led(bitset->names().at(static_cast<int>(i)),
                                   this, QSize(30, 30),
                                   bitset->valueAt(i) ? Led::State::On
                                                      : Led::State::Off);
                groupBoxLayout->addWidget(led, r, c);
                ++c;
            }
        }

        if (auto byte = dynamic_cast<Byte *>(element.get())) {
            auto bw = new ByteWidget(byte->name(),
                                     static_cast<quint8>(byte->value()));
            groupBoxLayout->addWidget(bw, r, c);
        }

        if (auto byte = dynamic_cast<Word *>(element.get())) {
            auto ww = new WordWidget(byte->name(), byte->value());
            groupBoxLayout->addWidget(ww, r, c);
        }

        blockLayout->addWidget(groupBox);
    }

    setLayout(blockLayout);
}
