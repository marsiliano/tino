#pragma once

#include "BlockWidget.hpp"
#include "Connector.hpp"
#include "Generator.hpp"

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

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

    QGridLayout *top;
    QLabel *lblPort;
    QLineEdit *linePort;
    QPushButton *btnConnect;
};
