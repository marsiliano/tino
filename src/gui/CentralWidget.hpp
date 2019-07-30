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

    QLabel *lblPort;
    QLineEdit *linePort;
    QPushButton *btnConnect;
    QPushButton *btnWrite;
    QPushButton *btnFile;
    QLabel *lblNbytes;

    std::vector<core::Block> blocks;
    Connector *c;
    std::string filename;

    MainSplitter *m;
    QTimer *writeTimer;

    int nBytes;
};
