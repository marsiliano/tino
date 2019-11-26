#include "MdiChild.hpp"

#include "Led.hpp"

#include <Bitset.hpp>
#include <QGridLayout>

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
                auto led = new Led(
                    bitset->descriptions().at(static_cast<int>(i)), this);
                // TODO: add value of bit
                groupBoxLayout->addWidget(led, r, c);
                ++c;
            }
        }

        blockLayout->addWidget(groupBox);
    }

    setLayout(blockLayout);
}
