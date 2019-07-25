#pragma once

#include "Block.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace core {

struct Settings {
    Settings()  = default;
    ~Settings() = default;

    std::string portName;
    int Parity;
    int BaudRate;
    int DataBits;
    int StopBits;
    int ServerAddress;
};

struct Parser {
    Parser() = delete;
    ~Parser() = default;

    static std::vector<core::Block> parse(std::string name);
    static rapidjson::Document getDocument(std::string name);
    static Settings getSettings(std::string name);
};
}
