#include <Bitset.hpp>
#include <Byte.hpp>
#include <ConfigParser.hpp>
#include <QDir>
#include <QtTest>
#include <Word.hpp>

#define STRINGIFY_INTERNAL(x) #x
#define STRINGIFY(x) STRINGIFY_INTERNAL(x)

class tst_Parser : public QObject
{
    Q_OBJECT

  private slots:
    void initTestCase();

    void throwIfNotExists();
    void withoutSettings();
    void normalSettings();
    void parseBitset();
    void parseByte();
    void parseWord();

  private:
    QString path_{};
    ConfigParser cp_;
};

void tst_Parser::initTestCase()
{
    path_ = STRINGIFY(TINO_PROJECT_DIR) + QStringLiteral("/tests/files/");
}

void tst_Parser::throwIfNotExists()
{
    QVERIFY_EXCEPTION_THROWN(cp_.parse(""), std::logic_error);
}

void tst_Parser::withoutSettings()
{
    auto config = cp_.parse(path_ + "empty.json");
    QVERIFY((config == Configuration{ Settings{}, Protocol{} }));
}

void tst_Parser::normalSettings()
{
    Settings right_settings;
    right_settings.portName          = "/dev/ttymxc1";
    right_settings.baudRate          = QSerialPort::BaudRate::Baud115200;
    right_settings.breakEnabled      = false;
    right_settings.dataBits          = QSerialPort::DataBits::Data8;
    right_settings.dataTerminalReady = false;
    right_settings.flowControl       = QSerialPort::FlowControl::NoFlowControl;
    right_settings.parity            = QSerialPort::Parity::NoParity;
    right_settings.requestToSend     = true;
    right_settings.stopBits          = QSerialPort::StopBits::OneStop;

    auto config = cp_.parse(path_ + "protocol.json");
    QVERIFY(config.settings == right_settings);
}

void tst_Parser::parseBitset()
{
    const auto config = cp_.parse(path_ + "1block-1group-flag.json");
    const auto &p     = config.protocol;
    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.front().description, "Block n1");
    QCOMPARE(p.blocks.front().elements.size(), size_t(1));
    auto b = dynamic_cast<Bitset *>(p.blocks.front().elements.front().get());
    QVERIFY(b != Q_NULLPTR);
    QCOMPARE(b->address(), 0x10);
    QCOMPARE(b->description(), "BitsArray n1");
    QCOMPARE(b->descriptions().size(), 8);

    QCOMPARE(p.elementMap.at(b->address())->description(), b->description());
}

void tst_Parser::parseByte()
{
    const auto config = cp_.parse(path_ + "protocol.json");
    const auto &p     = config.protocol;
    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.size(), 5);
    const auto b = p.blocks.back();
    QCOMPARE(b.description, "Control Panel Command Block");
    QCOMPARE(b.category, "Command");
    QCOMPARE(b.address, 0x0106);
    QCOMPARE(b.elements.size(), 5);
    QCOMPARE(b.elements.back()->name(), "ConsistencyCorrection");
    QCOMPARE(b.elements.back()->value(),
             0xC8); // FIXME: this fail because the value if > of int8_ts
    QCOMPARE(b.elements.back()->address(), 9);
    QCOMPARE(b.elements.back()->description(), "100-250, 200 no correction");
}

void tst_Parser::parseWord()
{
    const auto config = cp_.parse(path_ + "1block-1group-word.json");
    const auto &p     = config.protocol;
    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.front().description, "Block n1");
    QCOMPARE(p.blocks.front().elements.size(), size_t(1));
    auto w = dynamic_cast<Word *>(p.blocks.front().elements.front().get());
    QVERIFY(w != Q_NULLPTR);
    QCOMPARE(w->address(), 0x10);
    QCOMPARE(w->value(), 0x7DDA);
    QCOMPARE(w->description(), "Word description");

    QCOMPARE(p.elementMap.at(w->address())->description(), w->description());
}

QTEST_GUILESS_MAIN(tst_Parser)

#include "tst_Parser.moc"
