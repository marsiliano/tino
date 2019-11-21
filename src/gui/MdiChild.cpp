#include "MdiChild.hpp"

#include "Led.hpp"

#include <QGridLayout>

MdiChild::MdiChild(const Block &block, QWidget *parent) : QGroupBox(parent)
{
    setTitle(block.description);
    auto blockLayout = new QGridLayout(this);

    for (auto groupsCount = 0; groupsCount < block.groups.size();
         ++groupsCount) {
        const auto group    = block.groups.at(groupsCount);
        auto groupBox       = new QGroupBox(this);
        auto groupBoxLayout = new QGridLayout(groupBox);
        groupBox->setLayout(groupBoxLayout);
        groupBox->setTitle(group.description);
        int r = 0, c = 0;

        for (auto i = 0; i < group.bytes.front().flags.size(); ++i, ++c) {
            if (c == 4) {
                ++r;
                c = 0;
            }

            const auto description =
                group.bytes.front().flags.at(i).description;
            auto led = new Led(description, this);
            groupBoxLayout->addWidget(led, r, c);
        }

        blockLayout->addWidget(groupBox);
    }

    setLayout(blockLayout);
}

MdiChild::MdiChild(const Group &group, QWidget *parent) : QGroupBox(parent)
{
    setTitle(group.description);
    auto groupBoxLayout = new QGridLayout(this);
    int r = 0, c = 0;

    for (auto i = 0; i < group.bytes.front().flags.size(); ++i, ++c) {
        if (c == 4) {
            ++r;
            c = 0;
        }

        const auto description = group.bytes.front().flags.at(i).description;
        auto led               = new Led(description, this);
        groupBoxLayout->addWidget(led, r, c);
    }

    setLayout(groupBoxLayout);
}
