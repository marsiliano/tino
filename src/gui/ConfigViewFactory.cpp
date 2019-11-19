#include "ConfigViewFactory.hpp"

#include <QDockWidget>
#include <QStandardItemModel>
#include <QTreeView>

QDockWidget *ConfigViewFactory::makeConfigView(const Protocol &prot) const
{
    auto dock = new QDockWidget("Protocol");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    auto model                = new QStandardItemModel(dock);
    QStandardItem *parentItem = model->invisibleRootItem();
    for (int i = 0; i < 4; ++i) {
        QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
        parentItem->appendRow(item);
        parentItem = item;
    }

    auto view = new QTreeView(dock);
    view->setModel(model);
    dock->setWidget(view);
    return dock;
}
