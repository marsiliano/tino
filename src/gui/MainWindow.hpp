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
    void resizeSp();

  private:
    std::vector<core::Block> blocks;
    std::vector<ScrollBlock *> blocksWidget;
    Connector *c;

    Ui::MainWindow *ui;

    QBoxLayout *top; // btn connect, btnFile...
    QGridLayout *mainlayout;

    QSplitter *sp;
    std::vector<QSplitter *> spv;

    QLabel *lblPort;
    QLineEdit *linePort;
    QPushButton *btnConnect;
    QPushButton *btnFile;
};
