#include <MainWindow.hpp>
#include <QtTest>

class tst_MainWindow : public QObject
{
    Q_OBJECT

  private slots:
    void doNothingWhenImportFilenameEmpty();

  private:
    MainWindow m_mainWindow;
};

void tst_MainWindow::doNothingWhenImportFilenameEmpty()
{
    QSignalSpy spyImportFinished(&m_mainWindow, &MainWindow::importFinished);
    m_mainWindow.importConfig({});
    QCOMPARE(spyImportFinished.count(), 0);
}

QTEST_MAIN(tst_MainWindow)

#include "tst_MainWindow.moc"
