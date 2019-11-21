#pragma once

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui
{
class MainWindow;
}

class Configuration;

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  signals:
    void importFinished(QPrivateSignal);

  private slots:
    void selectFile();
    void createConfigView();

  private:
    Ui::MainWindow *ui;

    QScopedPointer<Configuration> m_config;
    QScopedPointer<QAction> m_serialConnect;
    QScopedPointer<QAction> m_serialSettings;

    void createMenuBar();
    void importConfig(const QString &filename);

    friend class tst_MainWindow;
};
