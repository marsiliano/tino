#pragma once

#include "Block.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <fstream>

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

namespace core
{
struct Generator {
    Generator() = delete;
    static std::vector<core::Block> parse(std::string name);
    static rapidjson::Document getDocument(std::string name);
    static Settings getSettings(std::string name);

    static core::Byte getByte1();
    static core::Byte getByte2();
    static core::Group getGroup1();
    static core::Group getGroup2();
    static core::Group getGroup3();
    static core::Block getBlock(int n);
};
} // namespace core
