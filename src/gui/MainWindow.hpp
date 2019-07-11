#pragma once

#include "BlockWidget.hpp"
#include "Connector.hpp"
#include "Generator.hpp"

#include <QMainWindow>
#include <QPushButton>
#include <yaml-cpp/yaml.h>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public slots:
    void activateConnection();

  private:
    Ui::MainWindow *ui;
    QPushButton *btnActivateConnection;
};
