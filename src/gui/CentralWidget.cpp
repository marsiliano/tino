#include "CentralWidget.hpp"

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    l = new QGridLayout(this);

    // top
    lblPort = new QLabel(this);
    lblPort->setText("Port: ");
    l->addWidget(lblPort, 0, 0, Qt::AlignLeft);
    l->setColumnStretch(0, 0);

    linePort = new QLineEdit(this);
    l->addWidget(linePort, 0, 1, Qt::AlignLeft);
    l->setColumnStretch(1, 0);

    btnConnect = new QPushButton(this);
    btnConnect->setText("connect");
    l->addWidget(btnConnect, 0, 2, Qt::AlignLeft);
    l->setColumnStretch(2, 0);

    // connect
    connect(btnConnect, &QPushButton::clicked, this, [&]() {
        if (c) {
            if (btnConnect->text() == "connect") {
                btnConnect->setText("disconect");
                c->startConnection(linePort->text());
            } else {
                btnConnect->setText("connect");
                c->endConnection();
            }
        }
    });

    // write something
    btnWrite = new QPushButton(this);
    btnWrite->setText("write");
    l->addWidget(btnWrite, 0, 3, Qt::AlignLeft);
    l->setColumnStretch(3, 0);

    connect(btnWrite, &QPushButton::clicked, this, [&]() {
        nBytes = 0;

        for (core::Block &tb : blocks)
            nBytes += c->writeBlock(tb);

        QString s = QString("%1 bytes written").arg(nBytes);
        lblNbytes->setText(s);
    });

    // load file
    btnFile = new QPushButton(this);
    btnFile->setText("load file");
    l->addWidget(btnFile, 0, 4, Qt::AlignLeft);
    l->setColumnStretch(4, 0);

    // draw blocks
    connect(btnFile, &QPushButton::clicked, this, [&]() {
        blocks = core::Generator::parse(
            QFileDialog::getOpenFileName(this, tr("Open config"), "/",
                                         tr("json Files (*.json)"))
                .toStdString());

        c = new Connector(this);
        m = new MainSplitter(blocks, this);

        l->addWidget(m, 1, 0, 1, 6, Qt::AlignLeft);
    });

    // nBytes
    lblNbytes = new QLabel(this);
    lblNbytes->setText("0 bytes written");
    l->addWidget(lblNbytes, 0, 5, Qt::AlignLeft);
    l->setColumnStretch(5, 2);
}
