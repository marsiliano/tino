#pragma once

#include "CentralWidget.hpp"

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  private:
    Ui::MainWindow *ui;
    CentralWidget *all;
};
