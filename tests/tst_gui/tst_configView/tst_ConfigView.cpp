#include <ConfigViewFactory.hpp>
#include <QDir>
#include <QDockWidget>
#include <QStandardItemModel>
#include <QTreeView>
#include <QtTest>

class tst_ConfigView : public QObject
{
    Q_OBJECT

  private slots:
    void initTestCase();
    void checkEmptyProtocol();

  private:
    Protocol m_protocol;
};

void tst_ConfigView::initTestCase()
{
    //    m_protocol.blocks.push_back();
}

void tst_ConfigView::checkEmptyProtocol()
{
    auto dock = ConfigViewFactory().makeConfigView({});
    QVERIFY(dock != Q_NULLPTR);
    const auto view = qobject_cast<QTreeView *>(dock->widget());
    QVERIFY(view != Q_NULLPTR);
    const auto model = qobject_cast<QStandardItemModel *>(view->model());
    QVERIFY(model != Q_NULLPTR);
    QVERIFY(model->rowCount() == 0);
}

QTEST_MAIN(tst_ConfigView)

#include "tst_ConfigView.moc"
