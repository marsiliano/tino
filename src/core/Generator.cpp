#include "Generator.hpp"

std::vector<core::Block> core::Generator::parse()
{
    // open the conf.json
    std::ifstream conf("/home/fsl/tino/conf.json", std::ios::in);
    std::cout << conf.is_open() ? "conf.json opened" : "conf.json NOT opened";

    // put conf.json in std::string s
    std::string s, t;
    while (getline(conf, t))
        s += t;

    // parse std::string s in json
    rapidjson::Document d;
    d.Parse(s.c_str());

    const rapidjson::Value &blocks = d["blocks"]; // get the main object

    std::vector<core::Block> all;

    for (int i = 0; i < blocks.Size(); ++i) {
        const auto &block = blocks[i];

        std::vector<core::Group> g;

        for (int j = 0; j < block["groups"].Size(); ++j) {
            const auto &group = block["groups"][j];

            std::vector<core::Byte> b;

            for (int k = 0; k < group["bytes"].Size(); ++k) {
                const auto &byte = group["bytes"][k];

                bool rw;
                std::vector<bool> v;
                std::vector<std::string> s;

                for (int l = 0; l < 8; ++l) {
                    // load bits
                }
                for (int l = 0; l < byte["desc"].Size(); ++l) {
                    // load desc
                }
                core::Byte tb(v, s, rw);
                b.push_back(tb);
            }
            core::Group tg(b, group["type"].GetBool());
            g.push_back(tg);
        }
        core::Block tblock(g, 0, block["name"].GetString());
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

core::Block core::Generator::getBlock1()
{
    std::vector<core::Group> vg = { getGroup1(), getGroup2() };
    core::Block bl(vg, 0, "block");
    return bl;
}

core::Block core::Generator::getBlock2()
{
    std::vector<core::Group> vg = { getGroup2(), getGroup1() };
    core::Block bl(vg, 0, "block");
    return bl;
}
