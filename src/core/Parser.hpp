#pragma once

#include "Block.hpp"
#include "Settings.hpp"

// json
//#include "rapidjson/document.h"
//#include "rapidjson/stringbuffer.h"
//#include "rapidjson/writer.h"

#include "../json/rapidjson/include/rapidjson/document.h"
#include "../json/rapidjson/include/rapidjson/stringbuffer.h"
#include "../json/rapidjson/include/rapidjson/writer.h"

namespace core
{
struct Parser {
    Parser()  = delete;
    ~Parser() = default;

    static std::vector<core::Block> parse(std::string name);
    static rapidjson::Document getDocument(std::string name);
    static Settings getSettings(std::string name);
};
} // namespace core
