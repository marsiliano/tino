#pragma once

#include <MdiChild.hpp>
#include <ModbusCom.hpp>
#include <QMainWindow>
#include <QScopedPointer>
#include <memory>

namespace Ui
{
class MainWindow;
}

class Configuration;
class QStandardItem;

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
    void customConfigViewContextMenu(const QPoint &point);

  private:
    Ui::MainWindow *ui;

    std::shared_ptr<Configuration> m_config;
    QScopedPointer<QAction> m_serialConnect;
    QScopedPointer<QAction> m_serialSettings;
    QScopedPointer<QDockWidget> m_configViewDock;

    QString m_importFilePath;

    std::unique_ptr<ModbusCom> m_modbus;
    std::vector<MdiChild *> m_mdiChilds;

    struct Error {
        bool error{ false };
        QString message{};
    };

    void createMenuBar();
    Error importConfig(const QString &filename);
    void createWidgetRequested(QStandardItem *item);
    void saveSettings();
    void loadSettings();

    friend class tst_MainWindow;
};
