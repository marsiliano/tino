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
    auto blockId    = 0;
    foreach (auto b, prot.blocks) {
        auto blockItem = makeItem(b);
        blockItem->setWhatsThis(QStringLiteral("block_%1").arg(blockId));
        auto groupId = 0;
        foreach (auto g, b.groups) {
            auto groupItem = makeItem(g);
            groupItem->setWhatsThis(QStringLiteral("block_%1_group_%2")
                                        .arg(blockId)
                                        .arg(groupId++));
            //            foreach (auto b, g.bytes) {
            //                auto byteItem = makeItem(b);
            //                foreach (auto f, b.flags) {
            //                    byteItem->appendRow(makeItem(f));
            //                }
            //                groupItem->appendRow(byteItem);
            //            }
            blockItem->appendRow(groupItem);
        }
        ++blockId;
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
