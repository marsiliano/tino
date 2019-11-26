#include <Bitset.hpp>
#include <Byte.hpp>
#include <ConfigParser.hpp>
#include <QDir>
#include <QtTest>
#include <Word.hpp>

class tst_Parser : public QObject
{
    Q_OBJECT

  private slots:
    void initTestCase();

    void throwIfNotExists();
    void withoutSettings();
    void normalSettings();
    void partialSettings();
    void parseBitset();
    void parseByte();
    void parseWord();

  private:
    QString path_{ QDir::currentPath() };
    ConfigParser cp_;
};

void tst_Parser::initTestCase()
{
    const auto last_slash = path_.lastIndexOf("build-");
    path_ = path_.remove(last_slash, (path_.size() - last_slash));
    if (path_.contains("tino")) {
        path_ += "tests/files/";
    } else {
        path_ += "tino/tests/files/";
    }
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
    right_settings.port_name           = "/dev/ttyUSB0";
    right_settings.baud_rate           = QSerialPort::BaudRate::Baud9600;
    right_settings.break_enabled       = true;
    right_settings.data_bits           = QSerialPort::DataBits::Data5;
    right_settings.data_terminal_ready = true;
    right_settings.flow_control    = QSerialPort::FlowControl::SoftwareControl;
    right_settings.parity          = QSerialPort::Parity::OddParity;
    right_settings.request_to_send = true;
    right_settings.stop_bits       = QSerialPort::StopBits::TwoStop;

    auto config = cp_.parse(path_ + "only-settings.json");
    QVERIFY((config == Configuration{ std::move(right_settings), Protocol{} }));
}

void tst_Parser::partialSettings()
{
    Settings right_settings;
    right_settings.port_name = QString("/dev/pts/5");
    right_settings.baud_rate = QSerialPort::BaudRate::Baud9600;

    auto config = cp_.parse(path_ + "only-settings-partial.json");
    QVERIFY((config == Configuration{ std::move(right_settings), Protocol{} }));
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
}

void tst_Parser::parseByte()
{
    const auto config = cp_.parse(path_ + "1block-1group-byte.json");
    const auto &p     = config.protocol;
    QVERIFY(!p.blocks.empty());
    QCOMPARE(p.blocks.front().description, "Block n1");
    QCOMPARE(p.blocks.front().elements.size(), size_t(2));
    auto b1 = dynamic_cast<Byte *>(p.blocks.front().elements.front().get());
    auto b2 = dynamic_cast<Byte *>(p.blocks.front().elements.back().get());
    QVERIFY(b1 != Q_NULLPTR);
    QVERIFY(b2 != Q_NULLPTR);
    QCOMPARE(b1->address(), 0x80);
    QCOMPARE(b2->address(), 0x90);
    QCOMPARE(b1->description(), "Byte n1");
    QCOMPARE(b2->description(), "Byte n2");
    QCOMPARE(b1->value(), 22);
    QCOMPARE(b2->value(), 44);
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
    QCOMPARE(w->address(), 0x1);
    QCOMPARE(w->description(), "Temperatura acqua lavaggio uscita caldaia");
}

QTEST_GUILESS_MAIN(tst_Parser)

#include "tst_Parser.moc"
