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

        auto bitset = dynamic_cast<Bitset *>(element.get());
        if (bitset != Q_NULLPTR) {
            for (size_t i = 0; i < bitset->bits.size(); ++i) {
                if (c == 4) {
                    ++r;
                    c = 0;
                }
                auto led = new Led(bitset->bitsDescriptions[i], this);
                groupBoxLayout->addWidget(led, r, c);
                ++c;
            }
        }

        blockLayout->addWidget(groupBox);
    }

    setLayout(blockLayout);
}
