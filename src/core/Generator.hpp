#pragma once
#include "Block.hpp"
#include "yaml-cpp/yaml.h"
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
    static core::Block getBlock();
};

} // namespace core
