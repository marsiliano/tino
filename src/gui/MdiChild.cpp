#include "MdiChild.hpp"

#include "Led.hpp"

#include <QGridLayout>

MdiChild::MdiChild(const Block &block, QWidget *parent) : QGroupBox(parent)
{
    setTitle(block.description);
    auto blockLayout = new QGridLayout(this);
    auto r           = 0;
    auto c           = 0;

    foreach (const auto &group, block.groups) {
        auto groupBox       = new QGroupBox(this);
        auto groupBoxLayout = new QGridLayout(groupBox);
        groupBox->setLayout(groupBoxLayout);
        groupBox->setTitle(group.description);

        foreach (const auto &flag, group.bytes.front().flags) {
            if (c == 4) {
                ++r;
                c = 0;
            }

            const auto description = flag.description;
            auto led               = new Led(description, this);
            groupBoxLayout->addWidget(led, r, c);
            ++c;
        }

        blockLayout->addWidget(groupBox);
    }

    setLayout(blockLayout);
}

MdiChild::MdiChild(const Group &group, QWidget *parent) : QGroupBox(parent)
{
    setTitle(group.description);
    auto groupBoxLayout = new QGridLayout(this);
    auto r              = 0;
    auto c              = 0;

    foreach (const auto &flag, group.bytes.front().flags) {
        if (c == 4) {
            ++r;
            c = 0;
        }

        const auto description = flag.description;
        auto led               = new Led(description, this);
        groupBoxLayout->addWidget(led, r, c);
        ++c;
    }

    setLayout(groupBoxLayout);
}
