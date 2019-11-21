#include <MainWindow.hpp>
#include <QtTest>

class tst_MainWindow : public QObject
{
    Q_OBJECT

  private slots:
    void initTestCase();
    void doNothingWhenImportFilenameEmpty();
    void doNothingWhenImportWrongFile();
    void emitWhenImportLooksFine();

    void avoidMultipleDockWithMultipleImport();

  private:
    QString filesPath;
};

void tst_MainWindow::initTestCase()
{
    auto path = QDir::currentPath();
    path      = path.remove(path.lastIndexOf("build"), path.size());
    path += "tests/files/";
    filesPath = path;
}

void tst_MainWindow::doNothingWhenImportFilenameEmpty()
{
    MainWindow mainWindow;
    QSignalSpy spyImportFinished(&mainWindow, &MainWindow::importFinished);
    mainWindow.importConfig({});
    QCOMPARE(spyImportFinished.count(), 0);
}

void tst_MainWindow::doNothingWhenImportWrongFile()
{
    MainWindow mainWindow;
    QVERIFY_EXCEPTION_THROWN(mainWindow.importConfig(filesPath + "wrong-file"),
                             std::logic_error);
}

void tst_MainWindow::emitWhenImportLooksFine()
{
    MainWindow mainWindow;
    QSignalSpy spyImportFinished(&mainWindow, &MainWindow::importFinished);
    mainWindow.importConfig(filesPath + "1block-1group-flag.json");
    QCOMPARE(spyImportFinished.count(), 1);
    QVERIFY(!m_mainWindow.m_config.isNull());
}

QTEST_MAIN(tst_MainWindow)

#include "tst_MainWindow.moc"
