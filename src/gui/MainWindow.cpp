#include "MainWindow.hpp"

#include "ConfigViewFactory.hpp"
#include "DialogAbout.hpp"
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

    create_menubar();

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

    emit importFinished({});
}

void MainWindow::createConfigView()
{
    auto dock = ConfigViewFactory().makeConfigView(m_config->protocol);
    dock->setParent(this);
    this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dock,
                        Qt::Orientation::Vertical);
}

void MainWindow::create_menubar()
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

    const auto help  = new QMenu("Help", ui->menuBar);
    const auto about = new QAction("About...", file);
    connect(about, &QAction::triggered, this, [&]() { DialogAbout().exec(); });
    help->addAction(about);
    ui->menuBar->addMenu(help);
}
