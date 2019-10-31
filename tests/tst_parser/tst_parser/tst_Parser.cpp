#include <ConfigParser.hpp>
#include <QDir>
#include <QtTest>

class tst_Parser : public QObject
{
    Q_OBJECT

  private slots:
    void initTestCase();

    void throw_if_not_exists();
    void without_settings();
    void normal_settings();
    void parse_flags();

  private:
    QString path_{ QDir::currentPath() };
    ConfigParser cp_;
};

void tst_Parser::initTestCase()
{
    const auto last_slash = path_.lastIndexOf("build-");
    path_ = path_.remove(last_slash, (path_.size() - last_slash));
    path_ += "tino/tests/files/";
}

void tst_Parser::throw_if_not_exists()
{
    QVERIFY_EXCEPTION_THROWN(cp_.parse(""), std::logic_error);
}

void tst_Parser::without_settings()
{
    auto config = cp_.parse(path_ + "empty.json");
    QVERIFY((config == Configuration{ Settings{}, Protocol{} }));
}

void tst_Parser::normal_settings()
{
    Settings right_settings;
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

void tst_Parser::parse_flags()
{
    auto settings = cp_.parse(path_ + "1block-1group-flag.json");
}

QTEST_GUILESS_MAIN(tst_Parser)

#include "tst_Parser.moc"
