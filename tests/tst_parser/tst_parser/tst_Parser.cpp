#include <ConfigParser.hpp>
#include <QDir>
#include <QtTest>

class tst_Parser : public QObject
{
    Q_OBJECT

  private slots:
    void initTestCase();

    void throw_if_not_exists();
    void parse_setting();

  private:
    QString path_{ QDir::currentPath() };
};

void tst_Parser::initTestCase()
{
    const auto last_slash = path_.lastIndexOf("build-");
    path_ = path_.remove(last_slash, (path_.size() - last_slash));
    path_ += "tino/tests/files/";
}

void tst_Parser::throw_if_not_exists()
{
    ConfigParser cp;
    QVERIFY_EXCEPTION_THROWN(cp.parse(""), std::logic_error);
}

void tst_Parser::parse_setting()
{
    ConfigParser cp;
    auto settings = cp.parse(path_ + "settings.json");
    QVERIFY(settings == core::Settings{});
}

QTEST_GUILESS_MAIN(tst_Parser)

#include "tst_Parser.moc"
