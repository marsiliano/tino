#include "Generator.hpp"
#include "Mask.hpp"

#include <QtTest>

class tst_Mask : public QObject
{
    Q_OBJECT

  private:
    QString expr;
    QString expb;
    widget::Mask *m;

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

    core::Byte b = core::Generator::getByte1(true);
    m            = new widget::Mask(&b, nullptr);
}

QString tst_Mask::getClr(const int i)
{
    QString cmp = m->getStyleBtn(i);
    cmp         = cmp.mid(cmp.indexOf("background-color:"), expr.length());
    return cmp;
}

void tst_Mask::tst_color()
{
    for (int i = 0; i < 8; ++i)
        QCOMPARE(getClr(i), (i % 2 == 0) ? expr : expb);
}

void tst_Mask::tst_click()
{
    QString clr;
    bool val;

    for (int i = 0; i < 8; ++i) {
        clr = getClr(i);
        val = m->valAt(i);

        m->clickBtn(i);

        QCOMPARE(val ? expb : expr, getClr(i));
        QCOMPARE((!val), m->valAt(i));
    }
}
QTEST_MAIN(tst_Mask)

#include "tst_Mask.moc"
