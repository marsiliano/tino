#include "Generator.hpp"

#include <sstream>

rapidjson::Document core::Generator::getDocument(std::string name)
{
    // open the conf.json
    std::ifstream conf(name, std::ios::in);
    std::cout << (conf.is_open() ? "conf.json opened" : "conf.json NOT opened");

    // put conf.json in std::string s
    std::string s, t;
    while (getline(conf, t))
        s += (t + '\n');

    // parse std::string s in json
    rapidjson::Document d;
    d.Parse(s.c_str());

    return d;
}

std::vector<core::Block> core::Generator::parse(std::string name)
{
    rapidjson::Document d = core::Generator::getDocument(name);
    const auto &blocks    = d["blocks"]; // get the main object

    std::vector<core::Block> all;

    std::for_each(blocks.Begin(), blocks.End(), [&](const auto &block) {
        std::vector<core::Group> g;

        std::for_each(
            block["groups"].Begin(), block["groups"].End(),
            [&](const auto &group) {
                std::vector<core::Byte> b;

                std::for_each(
                    group["bytes"].Begin(), group["bytes"].End(),
                    [&](const auto &byte) {
                        std::vector<bool> v;
                        std::vector<std::string> s;

                        for (int l = 0; l < 8; ++l)
                            v.push_back(byte["values"][l].GetBool());

                        for (int l = 0;
                             l < static_cast<int>(byte["desc"].Size()); ++l)
                            s.push_back(byte["desc"][l].GetString());

                        core::Byte tb(v, s, byte["rw"].GetBool());
                        b.push_back(tb);
                    });
                core::Group tg(b, group["type"].GetString()[0]);
                g.push_back(tg);
            });
        core::Block tblock(g, block["start"].GetInt(),
                           block["name"].GetString());
        all.push_back(tblock);
    });
    return all;
}

Settings core::Generator::getSettings(std::string name)
{
    rapidjson::Document d = core::Generator::getDocument(name);
    const auto &settings  = d["settings"]; // get the main object

    Settings s;
    s.portName      = settings["portName"].GetString();
    s.Parity        = settings["Parity"].GetInt();
    s.BaudRate      = settings["BaudRate"].GetInt();
    s.DataBits      = settings["DataBits"].GetInt();
    s.StopBits      = settings["StopBits"].GetInt();
    s.ServerAddress = settings["ServerAddress"].GetInt();
    return s;
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

    core::Byte b(v, s, true);
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
core::Group core::Generator::getGroup3()
{
    std::vector<core::Byte> vb = { getByte2(), getByte2(), getByte2() };
    core::Group g(vb, 'j');
    return g;
}

core::Block core::Generator::getBlock(int n)
{
    std::vector<core::Group> vg = { getGroup1(), getGroup2(), getGroup3() };

    std::stringstream stream;
    stream << "blockname" << n;

    core::Block bl(vg, (n - 1) * (vg.size() * 3), stream.str());
    return bl;
}

// template<typename T> std::string intToHex(T i)
//{
//    std::stringstream stream;
//    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) <<
//    std::hex
//           << i;
//    return stream.str();
//}
