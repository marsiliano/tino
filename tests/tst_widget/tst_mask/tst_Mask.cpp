#include "../../../src/widget/Mask.hpp"

#include <QtTest>

class tst_Mask : public QObject
{
    Q_OBJECT

  private slots:
    void tst_color();
};

void tst_Mask::tst_color()
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = { "prova" };
    core::Byte b(v, s, false);
    Mask m(b, nullptr);

    QColor clrr(255, 0, 0);
    QColor clrb(0, 0, 255);

    for (int i = 0; i < 8; i++) {
        QColor clr = m.b[i]->palette().button().color();

        if (i % 2 == 0)
            QCOMPARE(clr, clrr);
        else
            QCOMPARE(clr, clrb);
    }
}

QTEST_MAIN(tst_Mask)

#include "tst_Mask.moc"
