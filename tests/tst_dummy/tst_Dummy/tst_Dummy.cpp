#include <QtTest>

class tst_Dummy : public QObject
{
    Q_OBJECT

  private Q_SLOTS:
    void foo();
};

void tst_Dummy::foo()
{
    QEXPECT_FAIL("it is only for example", "it is only for example", Continue);
}

QTEST_APPLESS_MAIN(tst_Dummy)

#include "tst_Dummy.moc"
