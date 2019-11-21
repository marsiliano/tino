#include "MainWindow.hpp"

#include "ConfigViewFactory.hpp"
#include "DialogAbout.hpp"
#include "DialogSerialSettings.hpp"
#include "ui_MainWindow.h"

#include <ConfigParser.hpp>
#include <QDebug>
#include <QDesktopWidget>
#include <QDockWidget>
#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Tino");

    createMenubar();

    resize(QDesktopWidget().availableGeometry(this).size() * 0.3);

    connect(this, &MainWindow::importFinished, this,
            &MainWindow::createConfigView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectFile()
{
    const auto filename = QFileDialog::getOpenFileName(
        this, tr("Open Config File"),
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
        tr("Config File (*.json)"));

    if (filename.isNull() || filename.isEmpty()) {
        qDebug() << "filename not valid";
        return;
    }

    ConfigParser parser;
    m_config.reset(new Configuration{ parser.parse(filename) });

    if (m_config.isNull()) {
        qWarning() << "parsing error";
    }

    m_serialConnect->setEnabled(true);
    m_serialSettings->setEnabled(true);

    emit importFinished({});
}

void MainWindow::createConfigView()
{
    auto dock = ConfigViewFactory().makeConfigView(m_config->protocol);
    dock->setParent(this);
    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dock,
                        Qt::Orientation::Vertical);
}

void MainWindow::createMenubar()
{
    const auto file = new QMenu("File", ui->menuBar);

    const auto import = new QAction("Import file...", file);
    connect(import, &QAction::triggered, this, &MainWindow::selectFile);
    file->addAction(import);

    const auto quit = new QAction("Quit", file);
    quit->setShortcut(QKeySequence::StandardKey::Quit);
    connect(quit, &QAction::triggered, this, []() { qApp->quit(); });
    file->addAction(quit);

    ui->menuBar->addMenu(file);

    const auto comMenu = new QMenu("Com", ui->menuBar);

    m_serialConnect.reset(new QAction("Connect...", comMenu));
    m_serialConnect->setEnabled(false);
    connect(m_serialConnect.get(), &QAction::triggered, this,
            [&]() { m_serialConnect->setText("Disconnect..."); });
    comMenu->addAction(m_serialConnect.get());

    comMenu->addSeparator();

    m_serialSettings.reset(new QAction("Settings...", comMenu));
    m_serialSettings->setEnabled(false);
    connect(m_serialSettings.get(), &QAction::triggered, this,
            [&]() { DialogSerialSettings(&m_config->settings).exec(); });
    comMenu->addAction(m_serialSettings.get());

    ui->menuBar->addMenu(comMenu);

    const auto help  = new QMenu("Help", ui->menuBar);
    const auto about = new QAction("About...", file);
    connect(about, &QAction::triggered, this, []() { DialogAbout().exec(); });
    help->addAction(about);
    ui->menuBar->addMenu(help);
}
