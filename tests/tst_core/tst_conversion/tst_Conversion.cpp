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
    void tst_IntBool();
};

void tst_Conversion::initTestCase()
{
    b = core::Generator::getByte1(true);
}

void tst_Conversion::tst_BoolInt()
{
    QCOMPARE(b.getInt(), 170);
}

void tst_Conversion::tst_IntBool()
{
    std::vector<int> v = { 0, 255, 85, 170 };

    for (int i : v) {
        b.setInt(i);
        QCOMPARE(b.getInt(), i);
    }
}

QTEST_MAIN(tst_Conversion)

#include "tst_Conversion.moc"
