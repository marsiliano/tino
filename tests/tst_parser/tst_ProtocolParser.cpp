#include "../../src/core/Bitset.hpp"
#include "../../src/core/Byte.hpp"
#include "../../src/core/Word.hpp"
#include "../../src/parser/ConfigParser.hpp"

#include <QDir>
#include <QtTest>

class tst_ProtocolParser : public QObject
{
    Q_OBJECT

private slots:
    void throwIfNotExists();
    void withoutSettings();
    void normalSettings();
    void parseBitset();
    void parseByte();
    void parseWord();

private:
    QString path_{FILESPATH};
};

void tst_ProtocolParser::throwIfNotExists()
{
    ConfigParser parser("");
    QVERIFY_EXCEPTION_THROWN(parser.parse(), std::logic_error);
}

void tst_ProtocolParser::withoutSettings()
{
    ConfigParser parser(path_ + "empty.json");
    auto config = parser.parse();
    QVERIFY((config == Configuration{Settings{}, Protocol{}}));
}

void tst_ProtocolParser::normalSettings()
{
    Settings right_settings;
    right_settings.portName = "/dev/ttymxc1";
    right_settings.baudRate = QSerialPort::BaudRate::Baud115200;
    right_settings.breakEnabled = false;
    right_settings.dataBits = QSerialPort::DataBits::Data8;
    right_settings.dataTerminalReady = false;
    right_settings.flowControl = QSerialPort::FlowControl::NoFlowControl;
    right_settings.parity = QSerialPort::Parity::NoParity;
    right_settings.requestToSend = false;
    right_settings.stopBits = QSerialPort::StopBits::OneStop;

    ConfigParser parser(path_ + "protocol.json");
    auto config = parser.parse();
    QVERIFY(config.settings == right_settings);
}

void tst_ProtocolParser::parseBitset()
{
    ConfigParser parser(path_ + "protocol.json");
    const auto config = parser.parse();
    const auto &p = config.protocol;
    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.front().description, "");
    QCOMPARE(p.blocks.front().elements.size(), size_t(5));
    auto b = dynamic_cast<Bitset *>(p.blocks.front().elements.front().get());
    QVERIFY(b != Q_NULLPTR);
    QCOMPARE(b->address(), 262);
    QCOMPARE(b->description(), "BitsetDescription");
    QCOMPARE(b->descriptions().size(), 8);
    QCOMPARE(p.elementMap.at(b->address())->description(), b->description());
}

void tst_ProtocolParser::parseByte()
{
    ConfigParser parser(path_ + "protocol.json");
    const auto config = parser.parse();
    const auto &p = config.protocol;
    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.size(), std::size_t(1));
    const auto b = p.blocks.back();
    QCOMPARE(b.description, "");
    QCOMPARE(b.category, "Command");
    QCOMPARE(b.address, 0x0106);
    QCOMPARE(b.elements.size(), std::size_t(5));
    auto byte = b.elements.at(2);
    QCOMPARE(byte->name(), "UByte");
    auto v = byte->type() == Element::Type::SByte ? byte->sValue() : byte->uValue();
    QCOMPARE(v, 0x85);
    QCOMPARE(byte->address(), 264);
    QCOMPARE(byte->description(), "UByteDescr");
}

void tst_ProtocolParser::parseWord()
{
    ConfigParser parser(path_ + "protocol.json");
    const auto config = parser.parse();
    const auto &p = config.protocol;
    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.front().description, "");
    QCOMPARE(p.blocks.front().elements.size(), size_t(5));
    const auto w = p.blocks.back();
    QCOMPARE(w.description, "");
    QCOMPARE(w.category, "Command");
    QCOMPARE(w.address, 0x0106);
    QCOMPARE(w.elements.size(), std::size_t(5));
    auto word = w.elements.back();
    QCOMPARE(word->name(), "UWord");
    auto v = word->type() == Element::Type::SWord ? word->sValue() : word->uValue();
    QCOMPARE(v, 0x85);
    QCOMPARE(word->address(), 266);
    QCOMPARE(word->description(), "UWordDescr");
}

QTEST_GUILESS_MAIN(tst_ProtocolParser)

#include "tst_ProtocolParser.moc"
