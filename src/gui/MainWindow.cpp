#include "MainWindow.hpp"

#include "ConfigViewFactory.hpp"
#include "DialogAbout.hpp"
#include "DialogSerialSettings.hpp"
#include "ui_MainWindow.h"

#include <ConfigParser.hpp>
#include <MdiChild.hpp>
#include <QDebug>
#include <QDesktopWidget>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Tino");

    createMenuBar();

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

    importConfig(filename);
}

void MainWindow::createConfigView()
{
    ui->mdiArea->closeAllSubWindows();

    m_configViewDock.reset(
        ConfigViewFactory().makeConfigView(m_config->protocol));
    m_configViewDock->setObjectName("ConfigView");
    m_configViewDock->setParent(this);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,
                  m_configViewDock.get(), Qt::Orientation::Vertical);

    auto tree = dynamic_cast<QTreeView *>(m_configViewDock->widget());
    tree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tree, &QTreeView::customContextMenuRequested, this,
            &MainWindow::customConfigViewContextMenu);
}

void MainWindow::customConfigViewContextMenu(const QPoint &point)
{
    auto tree         = dynamic_cast<QTreeView *>(m_configViewDock->widget());
    QModelIndex index = tree->indexAt(point);

    if (index.isValid()) {
        auto *sModel = qobject_cast<QStandardItemModel *>(tree->model());
        auto *item   = sModel->itemFromIndex(index);
        const auto protocolItemMenu = new QMenu(this);
        const auto view             = new QAction("View", protocolItemMenu);
        view->setEnabled(item->whatsThis().contains("block"));

        connect(view, &QAction::triggered, this, [&]() {
            MdiChild *child;
            auto whatsThis = item->whatsThis();

            if (whatsThis.startsWith("block_") &&
                !whatsThis.contains("group_")) {
                auto blockId = whatsThis.split('_').at(1).toInt();
                child = new MdiChild(m_config->protocol.blocks.at(blockId));
            } else {
                auto blockId = whatsThis.split('_').at(1).toInt();
                auto groupId = whatsThis.split('_').at(3).toInt();
                child        = new MdiChild(
                    m_config->protocol.blocks.at(blockId).groups.at(groupId));
            }

            ui->mdiArea->addSubWindow(child);
            child->show();
        });

        protocolItemMenu->addAction(view);
        protocolItemMenu->exec(tree->viewport()->mapToGlobal(point));
    }
}

void MainWindow::createMenuBar()
{
    const auto file = new QMenu("File", ui->menuBar);

    const auto import = new QAction("Import file...", file);
    connect(import, &QAction::triggered, this, &MainWindow::selectFile);
    file->addAction(import);

    const auto quit = new QAction("Quit", file);
    quit->setShortcut(QKeySequence::StandardKey::Quit);
    connect(quit, &QAction::triggered, this, []() { QApplication::exit(); });
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

void MainWindow::importConfig(const QString &filename)
{
    if (filename.isNull() || filename.isEmpty()) {
        QMessageBox::warning(this, tr("Load configuration"),
                             tr("Filename not valid!"));
        return;
    }

    ConfigParser parser;
    m_config.reset(new Configuration{ parser.parse(filename) });

    if (m_config.isNull()) {
        QMessageBox::warning(this, tr("Load configuration"),
                             tr("Parsing configuration error!"));
        return;
    }

    m_serialConnect->setEnabled(true);
    m_serialSettings->setEnabled(true);

    emit importFinished({});
}
