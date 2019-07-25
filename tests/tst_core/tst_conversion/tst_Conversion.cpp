#include "Generator.hpp"

#include <QDebug>
#include <QtTest>

class tst_Conversion : public QObject
{
    Q_OBJECT
  private:
    core::Byte b;

  private slots:
    void initTestCase();
    void tst_BoolInt();
    void tst_IntBool0();
    void tst_IntBool255();
    void tst_IntBool85();
    void tst_IntBool32();
};

void tst_Conversion::initTestCase()
{
    b = core::Generator::getByte1();
}

void tst_Conversion::tst_BoolInt()
{
    QCOMPARE(b.getInt(), 85);
}

void tst_Conversion::tst_IntBool0()
{
    b.setInt(0);
    QCOMPARE(b.getInt(), 0);
}

void tst_Conversion::tst_IntBool255()
{
    b.setInt(255);
    QCOMPARE(b.getInt(), 255);
}

void tst_Conversion::tst_IntBool85()
{
    b.setInt(85);
    QCOMPARE(b.getInt(), 85);
}

void tst_Conversion::tst_IntBool32()
{
    b.setInt(32);
    QCOMPARE(b.getInt(), 32);
}

QTEST_MAIN(tst_Conversion)

#include "tst_Conversion.moc"
