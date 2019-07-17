#include "MainWindow.hpp"

#include <QDebug>
#include <QtTest>

class tst_Parse : public QObject
{
    Q_OBJECT
  private:
    std::vector<core::Block> all;
    std::vector<core::Block> cmp;

  private slots:
    void initTestCase();
    void tst_load();
    void parse();
    void compareSize();
};

void tst_Parse::initTestCase()
{
    qDebug() << "init";
    all = { core::Generator::getBlock1(), core::Generator::getBlock2() };
    qDebug() << "init1";
}

void tst_Parse::tst_load()
{
    std::ifstream conf("/home/fsl/tino/src/conf.json", std::ios::in);
    QVERIFY(conf.is_open());
}

void tst_Parse::compareSize()
{
    cmp = core::Generator::parse();
    QCOMPARE(all.size(), cmp.size());
}

void tst_Parse::parse()
{
    for (int i = 0; i < all.size(); ++i)
        QVERIFY(all[i] == cmp[i]);
}

QTEST_MAIN(tst_Parse)

#include "tst_Parse.moc"
