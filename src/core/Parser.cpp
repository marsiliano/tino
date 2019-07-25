#include "Parser.hpp"

#include <fstream>

rapidjson::Document core::Parser::getDocument(std::string name)
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

std::vector<core::Block> core::Parser::parse(std::string name)
{
    rapidjson::Document d = core::Parser::getDocument(name);
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

core::Settings core::Parser::getSettings(std::string name)
{
    rapidjson::Document d = core::Parser::getDocument(name);
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
