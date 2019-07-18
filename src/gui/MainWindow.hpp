#pragma once

#include "Connector.hpp"
#include "Generator.hpp"
#include "ScrollBlock.hpp"

#include <QFileDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QSplitter>

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
    void resizeEvent(QResizeEvent *e);

  private:
    std::vector<core::Block> blocks;
    std::vector<ScrollBlock *> blocksWidget;
    Connector *c;

    Ui::MainWindow *ui;

    QGridLayout *mainlayout; // blockWidgets
    QBoxLayout *top;         // btn connect, btnFile...
    QSplitter *sp;

    QLabel *lblPort;
    QLineEdit *linePort;
    QPushButton *btnConnect;
    QPushButton *btnFile;
};
