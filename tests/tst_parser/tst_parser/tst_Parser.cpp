#include <QtTest>

class tst_Parser : public QObject
{
    Q_OBJECT

  private slots:
    void parse_setting();
};

void tst_Parser::parse_setting()
{
    QVERIFY(false);
}

QTEST_GUILESS_MAIN(tst_Parser)

#include "tst_Parser.moc"
