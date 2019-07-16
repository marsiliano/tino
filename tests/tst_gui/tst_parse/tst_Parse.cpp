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
    //    void parse();
    void compareSize();
};

void tst_Parse::initTestCase()
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {
        "bitname1", "bitname2", "bitname3", "bitname4",
        "bitname5", "bitname6", "bitname7", "bitname8",
    };
    std::vector<std::string> s1 = { "bytename" };

    core::Byte b(v, s, true);
    std::vector<core::Byte> vb = { b, b, b };

    core::Byte b1(v, s1, false);
    std::vector<core::Byte> vb1 = { b1, b1, b1 };

    core::Group g(vb, 'm');
    core::Group g1(vb1, 'v');

    std::vector<core::Group> vg = { g, g1 };
    core::Block bl(vg, 0, "block");

    all = { bl, bl };
}

void tst_Parse::tst_load()
{
    std::ifstream conf("/home/fsl/tino/conf.json", std::ios::in);
    QVERIFY(conf.is_open());
}

void tst_Parse::compareSize()
{
    QCOMPARE(all.size(), cmp.size());
}

// void tst_Parse::parse()
//{
//    for (int i = 0; i < all.size(); ++i) {
//        QVERIFY(all[i] == cmp[i]);
//    }
//}

QTEST_MAIN(tst_Parse)

#include "tst_Parse.moc"
