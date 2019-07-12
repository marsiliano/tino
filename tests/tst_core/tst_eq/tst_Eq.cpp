#include "Generator.hpp"

#include <QDebug>
#include <QtTest>

class tst_Eq : public QObject
{
    Q_OBJECT

  private slots:
    void tst_EqBlock();
    void tst_EqGroup();
    void tst_EqByte();
    void tst_nByte();

  private:
};

void tst_Eq::tst_EqBlock()
{
    QVERIFY(core::Generator::getBlock() == core::Generator::getBlock());
}

void tst_Eq::tst_EqGroup()
{
    QVERIFY(core::Generator::getGroup1() == core::Generator::getGroup1());
    QVERIFY(core::Generator::getGroup2() == core::Generator::getGroup2());
}

void tst_Eq::tst_EqByte()
{
    QVERIFY(core::Generator::getByte1() == core::Generator::getByte1());
    QVERIFY(core::Generator::getByte2() == core::Generator::getByte2());
}

void tst_Eq::tst_nByte()
{
    QVERIFY(core::Generator::getBlock().getNbyte() == 6);
}

QTEST_MAIN(tst_Eq)

#include "tst_Eq.moc"
