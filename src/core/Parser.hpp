#pragma once

#include "Block.hpp"
#include "Settings.hpp"

// json
#include "json/json.h"

namespace core
{
struct Parser {
    Parser()  = delete;
    ~Parser() = default;

    static std::vector<core::Block> parse(std::string name);
    static Json::Value getRoot(std::string name);
    static Settings getSettings(std::string name);
};
} // namespace core
