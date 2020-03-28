#include "../../../src/core/Bitset.hpp"
#include "../../../src/core/Byte.hpp"
#include "../../../src/core/Word.hpp"
#include "../../../src/parser/ConfigParser.hpp"
#include "../../../src/parser/ParserImplXlsx.hpp"

#include <QDir>
#include <QtTest>

class tst_ParserXlsx : public QObject
{
    Q_OBJECT

private slots:
    void checkDigitalResources();
    void checkInputsNotDivisibleBy8();
    void checkAnalogResources();

private:
    QString path_{FILESPATH};
};


void tst_ParserXlsx::checkDigitalResources()
{
    ConfigParser parser(path_ + "protocol.xlsx");
    auto config = parser.parse();
    const auto &p = config.protocol;

    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.at(0).description, ParserImplXlsx::Tags::digitalInputs);
    QCOMPARE(p.blocks.at(0).elements.size(), size_t(6));
    QCOMPARE(p.blocks.at(1).description, ParserImplXlsx::Tags::digitalOutputs);
    QCOMPARE(p.blocks.at(1).elements.size(), size_t(6));
}

void tst_ParserXlsx::checkInputsNotDivisibleBy8()
{
    ConfigParser parser(path_ + "protocol_2.xlsx");
    auto config = parser.parse();
    const auto &p = config.protocol;

    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.front().description, ParserImplXlsx::Tags::digitalInputs);
    QCOMPARE(p.blocks.front().elements.size(), size_t(4));
}

void tst_ParserXlsx::checkAnalogResources()
{
    ConfigParser parser(path_ + "protocol.xlsx");
    auto config = parser.parse();
    const auto &p = config.protocol;

    QVERIFY(!p.blocks.empty());
    QVERIFY(p.blocks.size() >= 4);
    QCOMPARE(p.blocks.at(2).description, ParserImplXlsx::Tags::analogInputs);
    QCOMPARE(p.blocks.at(2).elements.size(), size_t(8));
    QCOMPARE(p.blocks.at(3).description, ParserImplXlsx::Tags::analogOutputs);
    QCOMPARE(p.blocks.at(3).elements.size(), size_t(8));
    QCOMPARE(p.blocks.at(4).description, ParserImplXlsx::Tags::encoders);
    QCOMPARE(p.blocks.at(4).elements.size(), size_t(8));
}

QTEST_GUILESS_MAIN(tst_ParserXlsx)

#include "tst_ParserXlsx.moc"
