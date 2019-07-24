#pragma once
#include "MainSplitter.hpp"

#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>

class CentralWidget : public QWidget
{
  public:
    CentralWidget(QWidget *parent);
    ~CentralWidget() = default;

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

    MainSplitter *m;

    int nBytes;
};
