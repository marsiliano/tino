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
    void compareSize();
    void compareBlockName();
    void compareBlockNbytes();
    void parse();
};

void tst_Parse::initTestCase()
{
    all = { core::Generator::getBlock1(), core::Generator::getBlock2() };
    cmp = core::Generator::parse("/home/fsl/tino/src/conf.json");
}

void tst_Parse::tst_load()
{
    std::ifstream conf("/home/fsl/tino/src/conf.json", std::ios::in);
    QVERIFY(conf.is_open());
}

void tst_Parse::compareSize()
{
    QCOMPARE(all.size(), cmp.size());
}

void tst_Parse::compareBlockName()
{
    for (int i = 0; i < all.size(); ++i)
        QVERIFY(all[i].getName() == cmp[i].getName());
}

void tst_Parse::compareBlockNbytes()
{
    for (int i = 0; i < all.size(); ++i)
        QVERIFY(all[i].getNbyte() == cmp[i].getNbyte());
}

void tst_Parse::parse()
{
    for (int i = 0; i < all.size(); ++i)
        QVERIFY(all[i] == cmp[i]);
}

QTEST_MAIN(tst_Parse)

#include "tst_Parse.moc"
