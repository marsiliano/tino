#include "MainWindow.hpp"

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto file = new QMenu("File", ui->menuBar);
    auto quit = new QAction("Quit", file);
    connect(quit, &QAction::triggered, this, []() { qApp->quit(); });
    file->addAction(quit);

    ui->menuBar->addMenu(file);

    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {
        "prova0", "prova1", "prova2", "prova3",
        "prova4", "prova5", "prova6", "prova7",
    };
    std::vector<std::string> s1 = { "prova" };

    core::Byte b(v, s, false);
    std::vector<core::Byte> vb = { b, b, b };

    core::Byte b1(v, s1, false);
    std::vector<core::Byte> vb1 = { b1, b1, b1 };

    core::Group g(vb, 'm');
    core::Group g1(vb1, 'v');

    std::vector<core::Group> vg = { g, g1 };

    core::Block block(vg, "block");

    auto B = new BlockWidget(block, this);
    B->setGeometry(0, 0, 800, 500);

    this->layout()->addWidget(B);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<core::Block> parse()
{
    std ::vector<core::Block> all;

    YAML::Node base =
        YAML::LoadFile("../../test/tst_gui/tst_parse/testConfig.yaml");
    YAML::Node blocklist = base["blocks"]; // get block names

    for (int i = 0; i < blocklist.size(); ++i) {
        YAML::Node blockNode =
            base[blocklist[i].as<std::string>()]; // get the block ==
        // names

        std::vector<core::Group> g;

        for (int j = 0; j < blockNode.size(); ++j) {
            YAML::Node groupNode =
                blockNode[blockNode[i].as<std::string>()]; // get the
                                                           // group
            YAML::Node bytesNode = groupNode["bytes"];

            std::vector<core::Byte> b;

            bool rw;
            std::vector<bool> v;
            std::vector<std::string> s;

            for (int k = 0; k < bytesNode.size(); ++k) {
                switch (k % 3) {
                    case 0:
                        rw = bytesNode[j];
                        break;
                    case 1:
                        v.clear();
                        for (int l = 0; l < bytesNode[j].size(); ++l) {
                            v.push_back(bytesNode[j][k].as<bool>());
                        }
                        break;
                    case 2:
                        s.clear();
                        for (int l = 0; l < bytesNode[j].size(); ++l) {
                            s.push_back(bytesNode[j][k].as<std::string>());
                        }
                        core::Byte tb(v, s, rw);
                        b.push_back(tb);
                        break;
                } // end switch
            }
            core::Group tg(b, groupNode["type"].as<char>());
            g.push_back(tg);
        } // end (int j = 0; j < blockNode.size(); ++j)
        core::Block tblock(g, blocklist[i].as<std::string>());
        all.push_back(tblock);
    }

    return all;
}
