#include "Generator.hpp"

#include <sstream>

core::Byte core::Generator::getByte1(bool rw)
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = {
        "bitname1", "bitname2", "bitname3", "bitname4",
        "bitname5", "bitname6", "bitname7", "bitname8",
    };

    core::Byte b(v, s, rw);
    return b;
}

core::Byte core::Generator::getByte2(bool rw)
{
    std::vector<bool> v = {
        true, false, true, false, true, false, true, false
    };
    std::vector<std::string> s = { "bytename" };

    core::Byte b(v, s, rw);
    return b;
}

core::Group core::Generator::getGroup1()
{
    std::vector<core::Byte> vb = { getByte1(false), getByte1(true),
                                   getByte1(true) };
    core::Group g(vb, 'm');
    return g;
}

core::Group core::Generator::getGroup2()
{
    std::vector<core::Byte> vb = { getByte2(false), getByte2(true),
                                   getByte2(true) };
    core::Group g(vb, 'v');
    return g;
}
core::Group core::Generator::getGroup3()
{
    std::vector<core::Byte> vb = { getByte2(false), getByte2(true),
                                   getByte2(true) };
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
