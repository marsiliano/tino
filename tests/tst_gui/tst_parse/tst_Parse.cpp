#include "MainWindow.hpp"

#include <QDebug>
#include <QtTest>

class tst_Parse : public QObject
{
    Q_OBJECT
  private:
    std::vector<core::Block> all;
    std::vector<core::Block> cmp;

  private slots:
    void initTestCase();
    void tst_load();
    //    void parse();
    void compareSize();
};

void tst_Parse::initTestCase()
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {
        "bitname1", "bitname2", "bitname3", "bitname4",
        "bitname5", "bitname6", "bitname7", "bitname8",
    };
    std::vector<std::string> s1 = { "bytename" };

    core::Byte b(v, s, true);
    std::vector<core::Byte> vb = { b, b, b };

    core::Byte b1(v, s1, false);
    std::vector<core::Byte> vb1 = { b1, b1, b1 };

    core::Group g(vb, 'm');
    core::Group g1(vb1, 'v');

    std::vector<core::Group> vg = { g, g1 };
    core::Block bl(vg, "block");

    all = { bl, bl };
}

void tst_Parse::tst_load()
{
    YAML::Node base = YAML::LoadFile("nfs.example.lan.yml");

    //    if (base.IsNull())
    //        qDebug() << "nnull";
    //    else
    //        qDebug() << "ok";
    QCOMPARE(base.IsNull(), false);
}

void tst_Parse::compareSize()
{
    //    YAML::Node base = YAML::Load("config.yaml");
    //    YAML::Node blocklist = base["blocks"]; // get block names

    //    for (int i = 0; i < blocklist.size(); ++i) {
    //        qDebug() << QString::fromStdString("block: " +
    //                                           blocklist[i].as<std::string>());
    //        YAML::Node blockNode =
    //            base[blocklist[i].as<std::string>()]; // get the block ==
    //        // names

    //        std::vector<core::Group> g;

    //        for (int j = 0; j < blockNode.size(); ++j) {
    //            YAML::Node groupNode =
    //                blockNode[blockNode[i].as<std::string>()]; // get the
    //                                                           // group
    //            YAML::Node bytesNode = groupNode["bytes"];

    //            std::vector<core::Byte> b;

    //            bool rw;
    //            std::vector<bool> v;
    //            std::vector<std::string> s;

    //            for (int k = 0; k < bytesNode.size(); ++k) {
    //                switch (k % 3) {
    //                    case 0:
    //                        rw = bytesNode[j];
    //                        break;
    //                    case 1:
    //                        v.clear();
    //                        for (int l = 0; l < bytesNode[j].size(); ++l)
    //                        {
    //                            v.push_back(bytesNode[j][k].as<bool>());
    //                        }
    //                        break;
    //                    case 2:
    //                        s.clear();
    //                        for (int l = 0; l < bytesNode[j].size(); ++l)
    //                        {
    //                            s.push_back(bytesNode[j][k].as<std::string>());
    //                        }
    //                        core::Byte tb(v, s, rw);
    //                        b.push_back(tb);
    //                        break;
    //                } // end switch
    //            }
    //            core::Group tg(b, groupNode["type"].as<char>());
    //            g.push_back(tg);
    //        } // end (int j = 0; j < blockNode.size(); ++j)
    //        core::Block tblock(g, blocklist[i].as<std::string>());
    //        all.push_back(tblock);
    //    }

    QCOMPARE(all.size(), cmp.size());
}

// void tst_Parse::parse()
//{
//    for (int i = 0; i < all.size(); ++i) {
//        QVERIFY(all[i] == cmp[i]);
//    }
//}

QTEST_MAIN(tst_Parse)

#include "tst_Parse.moc"
