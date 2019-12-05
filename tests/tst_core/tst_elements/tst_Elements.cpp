#include <Bitset.hpp>
#include <QDockWidget>
#include <QtTest>
#include <Word.hpp>

class tst_Elements : public QObject
{
    Q_OBJECT

  private slots:
    void checkBitset();
    void checkByte();
    void checkWord();
};

void tst_Elements::checkBitset()
{
    int8_t value = 47;
    Bitset b;

    b.setValue(value);
    QCOMPARE(b.valueAt(0), 1);
    QCOMPARE(b.valueAt(1), 1);
    QCOMPARE(b.valueAt(2), 1);
    QCOMPARE(b.valueAt(3), 1);
    QCOMPARE(b.valueAt(4), 0);
    QCOMPARE(b.valueAt(5), 1);
    QCOMPARE(b.valueAt(6), 0);
    QCOMPARE(b.valueAt(7), 0);

    value = 53;
    b.setAt(0, true);
    b.setAt(1, false);
    b.setAt(2, true);
    b.setAt(3, false);
    b.setAt(4, true);
    b.setAt(5, true);
    b.setAt(6, false);
    b.setAt(7, false);
    QCOMPARE(b.value(), value);
}

void tst_Elements::checkByte()
{
    Byte b{ "name", "description", 0x90, 99 };
    QCOMPARE(b.name(), "name");
    QCOMPARE(b.description(), "description");
    QCOMPARE(b.address(), 0x90);
    QCOMPARE(b.value(), 99);

    Byte bNeg{ "rewq", "rewq", 0xA0, -127 };
    QCOMPARE(bNeg.name(), "rewq");
    QCOMPARE(bNeg.description(), "rewq");
    QCOMPARE(bNeg.address(), 0xA0);
    QCOMPARE(bNeg.value(), -127);
}

void tst_Elements::checkWord()
{
    int16_t value = 4320;
    Word w{ {}, {}, {}, value };
    QCOMPARE(w.low(), 224);
    QCOMPARE(w.high(), 16);

    value = 2043;
    w     = Word{ "", "", 0x11, 251, 7 };
    QCOMPARE(w.value(), value);
}

QTEST_GUILESS_MAIN(tst_Elements)

#include "tst_Elements.moc"
