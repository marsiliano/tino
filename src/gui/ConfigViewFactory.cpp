#include "ConfigViewFactory.hpp"

#include <QDockWidget>
#include <QStandardItemModel>
#include <QTreeView>

QDockWidget *ConfigViewFactory::makeConfigView(const Protocol &prot)
{
    auto dock = new QDockWidget("Protocol");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    auto view  = new QTreeView(dock);
    auto model = new QStandardItemModel(view);

    const auto root = model->invisibleRootItem();
    foreach (auto b, prot.blocks) {
        auto blockItem = makeItem(b);
        foreach (auto g, b.groups) {
            auto groupItem = makeItem(g);
            foreach (auto b, g.bytes) {
                auto byteItem = makeItem(b);
                foreach (auto f, b.flags) {
                    byteItem->appendRow(makeItem(f));
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

template<typename T> QStandardItem *ConfigViewFactory::makeItem(T t)
{
    const auto str =
        t.description.isEmpty()
            ? QString("item_" + QString::number(m_emptyItemCounter++))
            : t.description;
    auto item = new QStandardItem(str);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    return item;
}
