#include "../../../src/widget/Mask.hpp"

#include <QDebug>
#include <QtTest>

class tst_Mask : public QObject
{
    Q_OBJECT

  private:
    QString expr;
    QString expb;
    Mask *m;

    QString getClr(const int i);

  private slots:
    void initTestCase();
    void tst_color();
    void tst_click();
};

void tst_Mask::initTestCase()
{
    expr = "background-color:#ff0000";
    expb = "background-color:#0000ff";

    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = { "prova" };
    core::Byte b(v, s, false);
    m = new Mask(b, nullptr);
}

QString tst_Mask::getClr(const int i)
{
    QString cmp = m->b[i]->styleSheet();
    cmp         = cmp.mid(cmp.indexOf("background-color:"), expr.length());
    return cmp;
}

void tst_Mask::tst_color()
{
    for (int i = 0; i < 8; ++i) {
        if (i % 2 == 0)
            QCOMPARE(getClr(i), expr);
        else
            QCOMPARE(getClr(i), expb);
    }
}

void tst_Mask::tst_click()
{
    QString clr;
    bool val;

    for (int i = 0; i < 8; ++i) {
        clr = getClr(i);
        val = m->val[i];

        m->doStuff(i);

        if (val == true) {
            QCOMPARE(expb, getClr(i));
            QCOMPARE(false, m->val[i]);
        } else {
            QCOMPARE(expr, getClr(i));
            QCOMPARE(true, m->val[i]);
        }
    }
}
QTEST_MAIN(tst_Mask)

#include "tst_Mask.moc"
