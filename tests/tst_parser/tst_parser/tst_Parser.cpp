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

void tst_Parser::without_settings()
{
    ConfigParser cp;
    auto settings = cp.parse(path_ + "nosettings.json");
    QVERIFY(settings == core::Settings{});
}

void tst_Parser::normal_settings()
{
    core::Settings right_settings;
    right_settings.baud_rate           = QSerialPort::BaudRate::Baud9600;
    right_settings.break_enabled       = true;
    right_settings.data_bits           = QSerialPort::DataBits::Data5;
    right_settings.data_terminal_ready = true;
    right_settings.flow_control    = QSerialPort::FlowControl::SoftwareControl;
    right_settings.parity          = QSerialPort::Parity::OddParity;
    right_settings.request_to_send = true;
    right_settings.stop_bits       = QSerialPort::StopBits::TwoStop;

    ConfigParser cp;
    auto settings = cp.parse(path_ + "settings.json");
    QVERIFY(settings == right_settings);
}

QTEST_GUILESS_MAIN(tst_Parser)

#include "tst_Parser.moc"
