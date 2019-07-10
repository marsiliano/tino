#include "Generator.hpp"

std::vector<core::Block> core::Generator::parse()
{
    std::vector<core::Block> all;

    YAML::Node base      = YAML::Load("config.yaml");
    YAML::Node blocklist = base["blocks"]; // get block names

    for (int i = 0; i < blocklist.size(); ++i) {
        qDebug() << QString::fromStdString("block: " +
                                           blocklist[i].as<std::string>());
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

core::Byte core::Generator::getByte1()
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {
        "bitname1", "bitname2", "bitname3", "bitname4",
        "bitname5", "bitname6", "bitname7", "bitname8",
    };

    core::Byte b(v, s, true);
    return b;
}

core::Byte core::Generator::getByte2()
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = { "bytename" };

    core::Byte b(v, s, false);
    return b;
}

core::Group core::Generator::getGroup1()
{
    std::vector<core::Byte> vb = { getByte1(), getByte1(), getByte1() };
    core::Group g(vb, 'm');
    return g;
}

core::Group core::Generator::getGroup2()
{
    std::vector<core::Byte> vb = { getByte2(), getByte2(), getByte2() };
    core::Group g(vb, 'v');
    return g;
}

core::Block core::Generator::getBlock()
{
    std::vector<core::Group> vg = { getGroup1(), getGroup2() };
    core::Block bl(vg, "block");
    return bl;
}
