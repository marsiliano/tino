set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Test SerialPort REQUIRED)

add_executable(tst_parser
    ../../src/core/Bitset.cpp     ../../src/core/Bitset.hpp
    ../../src/core/Block.cpp      ../../src/core/Block.hpp
    ../../src/core/Byte.cpp       ../../src/core/Byte.hpp
    ../../src/core/Element.cpp    ../../src/core/Element.hpp
    ../../src/core/Protocol.cpp   ../../src/core/Protocol.hpp
    ../../src/core/Settings.cpp   ../../src/core/Settings.hpp
    ../../src/core/Word.cpp       ../../src/core/Word.hpp

    ../../src/parser/ConfigParser.cpp   ../../src/parser/ConfigParser.hpp

    tst_Parser.cpp)

target_link_libraries(tst_parser PRIVATE Qt5::Core Qt5::Gui Qt5::Test Qt5::SerialPort)
