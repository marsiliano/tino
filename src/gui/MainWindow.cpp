#include "MainWindow.hpp"

#include "ConfigViewFactory.hpp"
#include "DialogAbout.hpp"
#include "DialogSerialSettings.hpp"
#include "ui_MainWindow.h"

#include <ConfigParser.hpp>
#include <Element.hpp>
#include <MdiChild.hpp>
#include <QDebug>
#include <QDesktopWidget>
#include <QDockWidget>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QScrollArea>
#include <QSettings>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Tino");

    createMenuBar();
    loadSettings();

    connect(this, &MainWindow::importFinished, this,
            &MainWindow::createConfigView);

    m_modbus = std::make_unique<ModbusCom>();
    connect(m_modbus.get(), &ModbusCom::updateGui, this, [this](int address) {
        for (const auto &mdi : m_mdiChilds) {
            if (mdi->hasElementWithAddress(address)) {
                mdi->updateGuiElemets();
                return;
            }
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectFile()
{
    const auto filename = QFileDialog::getOpenFileName(
        this, tr("Open Config File"), m_importFilePath,
        tr("Config File (*.json)"));

    auto result = importConfig(filename);
    if (result.error) {
        QMessageBox::warning(this, tr("Load configuration"),
                             tr(result.message.toUtf8().constData()));
    }
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

    if (!index.isValid()) {
        qWarning() << "index not valid" << index;
        return;
    }

    if (index.parent() != tree->rootIndex()) {
        qWarning() << "Not a root index";
        return;
    }

    auto sModel = qobject_cast<QStandardItemModel *>(tree->model());
    auto item   = sModel->itemFromIndex(index);
    const auto protocolItemMenu = new QMenu(this);
    const auto view             = new QAction("View", protocolItemMenu);
    view->setEnabled(item->accessibleText() == ConfigViewFactory::guiCreatable);

    connect(view, &QAction::triggered, this,
            [&]() { createWidgetRequested(item); });

    protocolItemMenu->addAction(view);
    protocolItemMenu->exec(tree->viewport()->mapToGlobal(point));
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
    connect(m_serialConnect.get(), &QAction::triggered, this, [&]() {
        if (m_modbus->isConnected()) {
            m_modbus->disconnectModbus();
            m_serialConnect->setText("Connect...");
        } else {
            if (!m_modbus->connectModbus(m_config->settings)) {
                QMessageBox::critical(this, tr("Tino"),
                                      tr("Modbus connection failed."));
                return;
            }
            m_serialConnect->setText("Disconnect...");
        }
    });
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

MainWindow::Error MainWindow::importConfig(const QString &filename)
{
    if (filename.isNull() || filename.isEmpty()) {
        return Error{ true, "Filename not valid!" };
    }

    ConfigParser parser;
    m_config.reset(new Configuration{ parser.parse(filename) });

    if (m_config == nullptr) {
        return Error{ true, "Parsing configuration error!" };
    }

    m_modbus->initializeServer(std::make_shared<Protocol>(m_config->protocol));

    m_serialConnect->setEnabled(true);
    m_serialSettings->setEnabled(true);

    emit importFinished({});

    m_importFilePath = filename;
    saveSettings();

    return {};
}

void MainWindow::createWidgetRequested(QStandardItem *item)
{
    const auto whatsThis = item->whatsThis();

    MdiChild *child;
    if (whatsThis.startsWith("block_") && !whatsThis.contains("group_")) {
        auto blockId = whatsThis.split('_').at(1).toInt();
        child        = new MdiChild(m_config->protocol.blocks.at(blockId));
    } else {
        auto blockId = whatsThis.split('_').at(1).toInt();
        child        = new MdiChild(m_config->protocol.blocks.at(blockId));
    }

    connect(child, &MdiChild::updateModbus, m_modbus.get(),
            &ModbusCom::writeRegister);
    m_mdiChilds.emplace_back(child);

    auto subWindow = new QWidget(ui->mdiArea);
    subWindow->setWindowTitle(child->title());
    subWindow->setLayout(new QVBoxLayout(subWindow));

    auto scrollArea = new QScrollArea(subWindow);
    subWindow->layout()->addWidget(scrollArea);
    scrollArea->setWidget(child);

    ui->mdiArea->addSubWindow(subWindow);
    subWindow->show();
}

void MainWindow::saveSettings()
{
    QSettings settings("Tino");
    settings.setValue("importFilePath", m_importFilePath);
}

void MainWindow::loadSettings()
{
    QSettings settings("Tino");
    auto desktop =
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    m_importFilePath = settings.value("importFilePath", desktop).toString();
}
