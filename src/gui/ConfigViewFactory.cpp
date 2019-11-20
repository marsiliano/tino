#include "ConfigViewFactory.hpp"

#include <QDockWidget>
#include <QStandardItemModel>
#include <QTreeView>

QDockWidget *ConfigViewFactory::makeConfigView(const Protocol &prot) const
{
    auto dock = new QDockWidget("Protocol");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    auto view  = new QTreeView(dock);
    auto model = new QStandardItemModel(view);

    const auto root = model->invisibleRootItem();
    foreach (auto b, prot.blocks) {
        auto blockItem = new QStandardItem(b.description);
        blockItem->setFlags(blockItem->flags() & ~Qt::ItemIsEditable);
        foreach (auto g, b.groups) {
            auto groupItem = new QStandardItem(g.description);
            groupItem->setFlags(groupItem->flags() & ~Qt::ItemIsEditable);
            foreach (auto b, g.bytes) {
                auto byteItem = new QStandardItem(b.description);
                byteItem->setFlags(byteItem->flags() & ~Qt::ItemIsEditable);
                foreach (auto f, b.flags) {
                    auto flagItem = new QStandardItem(f.description);
                    flagItem->setFlags(flagItem->flags() & ~Qt::ItemIsEditable);
                    byteItem->appendRow(flagItem);
                }
                groupItem->appendRow(byteItem);
            }
            blockItem->appendRow(groupItem);
        }
        root->appendRow(blockItem);
    }

    view->setModel(model);
    dock->setWidget(view);
    return dock;
}
