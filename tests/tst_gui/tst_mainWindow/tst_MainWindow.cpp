#include "../../../src/gui/MainWindow.hpp"

#include <QDockWidget>
#include <QtTest>

class tst_MainWindow : public QObject
{
    Q_OBJECT

private slots:
    void doNothingWhenImportFilenameEmpty();
    void doNothingWhenImportWrongFile();
    void emitWhenImportLooksFine();

    void avoidMultipleDockWithMultipleImport();

private:
    QString filesPath{FILESPATH};
};

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
    QVERIFY_EXCEPTION_THROWN(mainWindow.importConfig(filesPath + "wrong-file"), std::logic_error);
}

void tst_MainWindow::emitWhenImportLooksFine()
{
    MainWindow mainWindow;
    QSignalSpy spyImportFinished(&mainWindow, &MainWindow::importFinished);
    mainWindow.importConfig(filesPath + "protocol.json");
    QCOMPARE(spyImportFinished.count(), 1);
    QVERIFY(mainWindow.m_config);
}

void tst_MainWindow::avoidMultipleDockWithMultipleImport()
{
    MainWindow mainWindow;
    mainWindow.importConfig(filesPath + "protocol.json");
    mainWindow.importConfig(filesPath + "protocol.json");
    QCOMPARE(mainWindow.findChildren<QDockWidget *>("ConfigView").count(), 1);
}

QTEST_MAIN(tst_MainWindow)

#include "tst_MainWindow.moc"
