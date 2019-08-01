#include "Generator.hpp"
#include "Parser.hpp"

#include <QDebug>
#include <QtTest>
#include <fstream>

class tst_Parser : public QObject
{
    Q_OBJECT
  private:
    std::vector<core::Block> all;
    std::vector<core::Block> cmp;
    long unsigned int i;
    std::string conf;
    std::string settings;

  private slots:
    void initTestCase();
    void tst_load();
    void compareSize();
    void compareBlockName();
    void compareBlockNbytes();
    void parse();
    void parseSettings();
};

void tst_Parser::initTestCase()
{
    conf     = "../../../../tino/jsons/conf.json";
    settings = "../../../../tino/jsons/quadro-video-settings.json";
    // you should look at the path relative to the tst_gui executable
    all = {
        core::Generator::getBlock(1), core::Generator::getBlock(2),
        core::Generator::getBlock(3), core::Generator::getBlock(4),
        core::Generator::getBlock(5),
    };
    core::Parser::parse(conf, cmp);
}

void tst_Parser::tst_load()
{
    std::ifstream fconf(conf, std::ios::in);
    QVERIFY(fconf.is_open());

    std::ifstream fsettings(settings, std::ios::in);
    QVERIFY(fsettings.is_open());
}

void tst_Parser::compareSize()
{
    QCOMPARE(all.size(), cmp.size());
}

void tst_Parser::compareBlockName()
{
    for (i = 0; i < all.size(); ++i)
        QCOMPARE(QString::fromStdString(all[i].getName()),
                 QString::fromStdString(cmp[i].getName()));
}

void tst_Parser::compareBlockNbytes()
{
    for (i = 0; i < all.size(); ++i)
        QCOMPARE(all[i].getNbyte(), cmp[i].getNbyte());
}

void tst_Parser::parse()
{
    for (i = 0; i < all.size(); ++i)
        QVERIFY(all[i] == cmp[i]);
}

void tst_Parser::parseSettings()
{
    core::Settings s;
    s.portName      = "auto";
    s.Parity        = 0;
    s.BaudRate      = 57600;
    s.DataBits      = 8;
    s.StopBits      = 1;
    s.ServerAddress = 1;

    core::Settings s1;
    core::Parser::getSettings(settings, s1);

    QVERIFY(s == s1);
}

QTEST_MAIN(tst_Parser)

#include "tst_Parser.moc"
