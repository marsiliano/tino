#include "Block.hpp"

#include <QDebug>
#include <QtTest>

class tst_Eq : public QObject
{
    Q_OBJECT

  private slots:
    void tst_EqBlock();
    void tst_EqGroup();
    void tst_EqByte();

  private:
    core::Byte getByte1();
    core::Byte getByte2();
    core::Group getGroup1();
    core::Group getGroup2();
    core::Block getBlock();
};

core::Byte tst_Eq::getByte1()
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {
        "bitname1", "bitname2", "bitname3", "bitname4",
        "bitname5", "bitname6", "bitname7", "bitname8",
    };

    core::Byte b(v, s, true);
    return b;
}

core::Byte tst_Eq::getByte2()
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = { "bytename" };

    core::Byte b(v, s, false);
    return b;
}

core::Group tst_Eq::getGroup1()
{
    std::vector<core::Byte> vb = { getByte1(), getByte1(), getByte1() };
    core::Group g(vb, 'm');
    return g;
}

core::Group tst_Eq::getGroup2()
{
    std::vector<core::Byte> vb = { getByte2(), getByte2(), getByte2() };
    core::Group g(vb, 'v');
    return g;
}

core::Block tst_Eq::getBlock()
{
    std::vector<core::Group> vg = { getGroup1(), getGroup2() };
    core::Block bl(vg, "block");
    return bl;
}

void tst_Eq::tst_EqBlock()
{
    QVERIFY(getBlock() == getBlock());
}

void tst_Eq::tst_EqGroup()
{
    QVERIFY(getGroup1() == getGroup1());
    QVERIFY(getGroup2() == getGroup2());
}

void tst_Eq::tst_EqByte()
{
    QVERIFY(getByte1() == getByte1());
    QVERIFY(getByte2() == getByte2());
}

QTEST_MAIN(tst_Eq)

#include "tst_Eq.moc"
