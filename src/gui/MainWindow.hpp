#pragma once

#include <BlockWidget.hpp>
#include <QMainWindow>
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

    std::vector<core::Block> parse();

  private:
    Ui::MainWindow *ui;
};
