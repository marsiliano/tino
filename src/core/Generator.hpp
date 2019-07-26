#pragma once

#include "Block.hpp"

namespace core
{
struct Generator {
    Generator()  = delete;
    ~Generator() = default;

    static core::Byte getByte1(bool rw);
    static core::Byte getByte2(bool rw);
    static core::Group getGroup1();
    static core::Group getGroup2();
    static core::Group getGroup3();
    static core::Block getBlock(int n);
};
} // namespace core
