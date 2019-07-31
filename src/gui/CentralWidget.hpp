#pragma once
#include "MainSplitter.hpp"

#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>

class CentralWidget : public QWidget
{
  public:
    CentralWidget(QWidget *parent);
    ~CentralWidget();

    void clean();
    void stopWriteTimer();

  private:
    QGridLayout *l;

    std::vector<core::Block> blocks;
    Connector *c;

    MainSplitter *m;

    QLabel *lblPort;
    QLineEdit *linePort;
    QPushButton *btnConnect;
    QPushButton *btnWrite;
    QPushButton *btnFile;
    QLabel *lblNbytes;
    QTimer *writeTimer;

    int nBytes;
    std::string filename;

    int btnConnectState;
};
