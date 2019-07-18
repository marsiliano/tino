#pragma once
#include "Block.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <fstream>

namespace core
{
class Generator
{
  public:
    static std::vector<core::Block> parse();
    static core::Byte getByte1();
    static core::Byte getByte2();
    static core::Group getGroup1();
    static core::Group getGroup2();
    static core::Group getGroup3();
    static core::Block getBlock1();
    static core::Block getBlock2();
};

} // namespace core
