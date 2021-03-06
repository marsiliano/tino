#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "ConfigViewFactory.hpp"
#include "DialogAbout.hpp"
#include "DialogSerialSettings.hpp"
#include "MdiChild.hpp"

#include "../parser/ConfigParser.hpp"

#include "../core/Element.hpp"

#include <QDockWidget>
#include <QFileDialog>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QSettings>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QToolBar>
#include <QTreeView>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Tino");
    this->setWindowIcon(QIcon(":/logos/vector/isolated-layout.svg"));

    createActions();
    createMenuBar();
    createToolBar();
    loadSettings();

    connect(this, &MainWindow::importFinished, this, &MainWindow::createConfigView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("Tino");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::selectFile()
{
    const auto filename = QFileDialog::getOpenFileName(this,
                                                       tr("Open Config File"),
                                                       m_importFilePath,
                                                       tr("Config File (*.json)"));

    auto result = importConfig(filename);
    if (result.error) {
        QMessageBox::warning(this,
                             tr("Load configuration"),
                             tr(result.message.toUtf8().constData()));
    }
}

void MainWindow::createConfigView()
{
    ui->mdiArea->closeAllSubWindows();

    m_configViewDock.reset(ConfigViewFactory().makeConfigView(m_config->protocol));
    m_configViewDock->setObjectName("ConfigView");
    m_configViewDock->setFeatures(m_configViewDock->features() & ~QDockWidget::DockWidgetClosable);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,
                  m_configViewDock.get(),
                  Qt::Orientation::Vertical);

    auto tree = dynamic_cast<QTreeView *>(m_configViewDock->widget());
    tree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tree,
            &QTreeView::customContextMenuRequested,
            this,
            &MainWindow::customConfigViewContextMenu);
}

void MainWindow::customConfigViewContextMenu(const QPoint &point)
{
    auto tree = dynamic_cast<QTreeView *>(m_configViewDock->widget());
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
    auto item = sModel->itemFromIndex(index);
    const auto protocolItemMenu = new QMenu(this);
    const auto view = new QAction("View", protocolItemMenu);
    view->setEnabled(item->accessibleText() == ConfigViewFactory::guiCreatable);

    connect(view, &QAction::triggered, this, [&]() { createWidgetRequested(item); });

    protocolItemMenu->addAction(view);
    protocolItemMenu->exec(tree->viewport()->mapToGlobal(point));
}

void MainWindow::connectClient()
{
    if (!m_modbus->connectModbus(m_config->settings)) {
        QMessageBox::critical(this, tr("Tino"), tr("Modbus connection failed."));
        return;
    }

    m_actions[Actions::Connect]->setEnabled(false);
    m_actions[Actions::Disconnect]->setEnabled(true);
}

void MainWindow::disconnectClient()
{
    m_modbus->disconnectModbus();
    m_actions[Actions::Connect]->setEnabled(true);
    m_actions[Actions::Disconnect]->setEnabled(false);

    const auto list = ui->mdiArea->subWindowList();
    std::for_each(std::cbegin(list), std::cend(list), [](const auto &w) {
        auto mdiChild = dynamic_cast<MdiChild *>(w->widget());
        mdiChild->resetToDefault();
    });
}

void MainWindow::createActions()
{
    m_actions[Actions::Open] = std::make_unique<QAction>(tr("Open File..."));
    m_actions[Actions::Open]->setIcon(QIcon(":/flat/folder.png"));
    connect(m_actions[Actions::Open].get(), &QAction::triggered, this, &MainWindow::selectFile);

    m_actions[Actions::Connect] = std::make_unique<QAction>(tr("Connect"));
    m_actions[Actions::Connect]->setIcon(QIcon(":/flat/connected.png"));
    m_actions[Actions::Connect]->setEnabled(false);
    connect(m_actions[Actions::Connect].get(),
            &QAction::triggered,
            this,
            &MainWindow::connectClient);

    m_actions[Actions::Disconnect] = std::make_unique<QAction>(tr("Disconnect"));
    m_actions[Actions::Disconnect]->setIcon(QIcon(":/flat/disconnected.png"));
    m_actions[Actions::Disconnect]->setEnabled(false);
    connect(m_actions[Actions::Disconnect].get(),
            &QAction::triggered,
            this,
            &MainWindow::disconnectClient);

    m_actions[Actions::Settings] = std::make_unique<QAction>(tr("Setting..."));
    m_actions[Actions::Settings]->setIcon(QIcon(":/flat/settings.png"));
    m_actions[Actions::Settings]->setEnabled(false);
    connect(m_actions[Actions::Settings].get(), &QAction::triggered, this, [&]() {
        DialogSerialSettings(&m_config->settings).exec();
    });

    m_actions[Actions::About] = std::make_unique<QAction>(tr("About..."));
    m_actions[Actions::About]->setIcon(QIcon(":/flat/info.png"));
    connect(m_actions[Actions::About].get(), &QAction::triggered, this, []() {
        DialogAbout().exec();
    });

    m_actions[Actions::Quit] = std::make_unique<QAction>(tr("Quit"));
    m_actions[Actions::Quit]->setIcon(QIcon(":/flat/quit.png"));
    m_actions[Actions::Quit]->setShortcut(QKeySequence::StandardKey::Quit);
    connect(m_actions[Actions::Quit].get(), &QAction::triggered, this, []() {
        QApplication::exit();
    });
}

void MainWindow::createMenuBar()
{
    const auto file = new QMenu("File", ui->menuBar);
    file->addAction(m_actions[Actions::Open].get());
    file->addAction(m_actions[Actions::Quit].get());
    ui->menuBar->addMenu(file);

    const auto comMenu = new QMenu(tr("Communication"), ui->menuBar);
    comMenu->addAction(m_actions[Actions::Connect].get());
    comMenu->addAction(m_actions[Actions::Disconnect].get());
    comMenu->addSeparator();
    comMenu->addAction(m_actions[Actions::Settings].get());
    ui->menuBar->addMenu(comMenu);

    const auto help = new QMenu("Help", ui->menuBar);
    help->addAction(m_actions[Actions::About].get());
    ui->menuBar->addMenu(help);
}

void MainWindow::createToolBar()
{
    m_toolbar = new QToolBar(this);
    m_toolbar->setObjectName("toolbar");
    m_toolbar->setMovable(false);
    addToolBar(Qt::ToolBarArea::TopToolBarArea, m_toolbar);
    m_toolbar->addAction(m_actions[Actions::Open].get());
    m_toolbar->addAction(m_actions[Actions::Connect].get());
    m_toolbar->addAction(m_actions[Actions::Disconnect].get());
    m_toolbar->addAction(m_actions[Actions::Settings].get());
}

MainWindow::Error MainWindow::importConfig(const QString &filename)
{
    if (filename.isNull() || filename.isEmpty()) {
        return Error{true, "Filename not valid!"};
    }

    ConfigParser parser;
    m_config = std::make_unique<Configuration>(parser.parse(filename));

    if (m_config == nullptr) {
        return Error{true, "Parsing configuration error!"};
    }

    m_modbus = std::make_unique<ModbusCom>(m_config->protocol);
    connect(m_modbus.get(), &ModbusCom::updateGui, this, [this](int address) {
        const auto list = ui->mdiArea->subWindowList();
        for (const auto &w : list) {
            auto mdi = dynamic_cast<MdiChild *>(w->widget());
            // FIXME: maybe some ValueWidget are not refreshed
            if (mdi->hasElementWithAddress(address)) {
                mdi->updateGuiElemets();
                return;
            }
        }
    });

    m_actions[Actions::Connect]->setEnabled(true);
    m_actions[Actions::Disconnect]->setEnabled(false);
    m_actions[Actions::Settings]->setEnabled(true);

    emit importFinished({});

    m_importFilePath = filename;
    saveSettings();

    return {};
}

void MainWindow::createWidgetRequested(QStandardItem *item)
{
    const auto whatsThis = item->whatsThis();
    const auto blockId = whatsThis.split('_').at(1).toInt();
    const auto block = m_config->protocol.blocks.at(blockId);

    if (setFocusIfAlreadyExists(block)) {
        return;
    }

    const auto child = new MdiChild(block);
    connect(child, &MdiChild::updateModbus, m_modbus.get(), &ModbusCom::writeRegister);
    ui->mdiArea->addSubWindow(child);
    child->show();
}

void MainWindow::saveSettings()
{
    QSettings settings("Tino");
    settings.setValue("importFilePath", m_importFilePath);
}

void MainWindow::loadSettings()
{
    QSettings settings("Tino");
    auto desktop = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    m_importFilePath = settings.value("importFilePath", desktop).toString();
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

bool MainWindow::setFocusIfAlreadyExists(const Block &block) const
{
    const auto list = ui->mdiArea->subWindowList();
    const auto it = std::find_if(std::cbegin(list), std::cend(list), [&](const auto &k) {
        return k->windowTitle() == block.description;
    });

    if (it == list.cend()) {
        return false;
    }

    list.at(std::distance(std::cbegin(list), it))->setFocus();
    return true;
}
