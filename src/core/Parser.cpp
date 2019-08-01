#include "Parser.hpp"

#include <fstream>

Json::Value core::Parser::getRoot(const std::string &name)
{
    // open the conf.json
    std::ifstream conf(name, std::ios::in);
    std::cout << (conf.is_open() ? "conf.json opened" : "conf.json NOT opened");

    Json::Value root;
    conf >> root;

    return root;
}

void core::Parser::parse(std::string name, std::vector<core::Block> &all)
{
    Json::Value root         = core::Parser::getRoot(name);
    const Json::Value blocks = root["blocks"]; // get the main object
    all.clear();

    std::for_each(blocks.begin(), blocks.end(), [&](const Json::Value &block) {
        std::vector<core::Group> g;

        std::for_each(
            block["groups"].begin(), block["groups"].end(),
            [&](const Json::Value &group) {
                std::vector<core::Byte> b;

                std::for_each(
                    group["bytes"].begin(), group["bytes"].end(),
                    [&](const Json::Value &byte) {
                        std::vector<bool> v;
                        std::vector<std::string> s;

                        for (int l = 0; l < 8; ++l)
                            v.push_back(byte["values"][l].asBool());

                        for (int l = 0;
                             l < static_cast<int>(byte["desc"].size()); ++l)
                            s.push_back(byte["desc"][l].asString());

                        core::Byte tb(v, s, byte["write"].asBool(),
                                      byte["name"].asString());
                        b.push_back(tb);
                    });
                core::Group tg(b, group["type"].asString()[0]);
                g.push_back(tg);
            });
        core::Block tblock(g, block["start"].asInt(), block["name"].asString());
        all.push_back(tblock);
    });
}

void core::Parser::getSettings(std::string name, core::Settings &s)
{
    Json::Value root     = core::Parser::getRoot(name);
    const auto &settings = root["settings"]; // get the main object

    s.portName      = settings["portName"].asString();
    s.Parity        = settings["Parity"].asInt();
    s.BaudRate      = settings["BaudRate"].asInt();
    s.DataBits      = settings["DataBits"].asInt();
    s.StopBits      = settings["StopBits"].asInt();
    s.ServerAddress = settings["ServerAddress"].asInt();
    s.refreshTime   = settings["refreshTime"].asInt();
}
