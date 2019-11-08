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

  private slots:
    void selectFile();

  private:
    Ui::MainWindow *ui;

    QScopedPointer<Configuration> m_config;

    void create_menubar();
};
