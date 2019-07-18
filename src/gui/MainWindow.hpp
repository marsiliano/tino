#pragma once

#include "BlockWidget.hpp"
#include "Connector.hpp"
#include "Generator.hpp"

#include <QFileDialog>
#include <QLineEdit>
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

  private:
    std::vector<core::Block> blocks;
    std::vector<BlockWidget *> blocksWidget;
    Connector *c;
    int blockWidth;

    Ui::MainWindow *ui;

    QGridLayout *mainlayout; // blockWidgets
    QBoxLayout *top;         // btn connect, btnFile...

    QLabel *lblPort;
    QLineEdit *linePort;
    QPushButton *btnConnect;
    QPushButton *btnFile;
};
