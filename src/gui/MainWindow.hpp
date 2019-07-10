#pragma once

#include "BlockWidget.hpp"
#include "Generator.hpp"

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

    std::vector<core::Block> parse(std::string flname);

  private:
    Ui::MainWindow *ui;
};
