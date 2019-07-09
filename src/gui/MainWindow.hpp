#pragma once

#include "../widget/BlockWidget.hpp"
#include "../yaml/yaml-cpp/include/yaml-cpp/yaml.h"

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
    ~MainWindow();

    std::vector<core::Block> parse(std::string filename);

  private:
    Ui::MainWindow *ui;
};
