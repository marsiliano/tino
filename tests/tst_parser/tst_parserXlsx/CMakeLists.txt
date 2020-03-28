set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${PROJECT_SOURCE_DIR}/3rd-party/qtxlsx/src)

find_package(Qt5 COMPONENTS Core Gui Test SerialPort REQUIRED)

add_executable(tst_parserXlsx
    ../../../src/core/Bitset.cpp     ../../../src/core/Bitset.hpp
    ../../../src/core/Block.cpp      ../../../src/core/Block.hpp
    ../../../src/core/Byte.cpp       ../../../src/core/Byte.hpp
    ../../../src/core/Element.cpp    ../../../src/core/Element.hpp
    ../../../src/core/Protocol.cpp   ../../../src/core/Protocol.hpp
    ../../../src/core/Settings.cpp   ../../../src/core/Settings.hpp
    ../../../src/core/Word.cpp       ../../../src/core/Word.hpp
    ../../../src/core/DoubleSWord.cpp ../../../src/core/DoubleSWord.hpp

    ../../../src/parser/ConfigParser.cpp   ../../../src/parser/ConfigParser.hpp
    ../../../src/parser/ParserImplJson.cpp ../../../src/parser/ParserImplJson.hpp
    ../../../src/parser/ParserImplXlsx.cpp ../../../src/parser/ParserImplXlsx.hpp
    ../../../src/parser/IParserImplementation.hpp
    ../../../src/parser/Configuration.hpp

    tst_ParserXlsx.cpp)

target_link_libraries(tst_parserXlsx PRIVATE Qt5::Core Qt5::Gui Qt5::Test Qt5::SerialPort
                                     PUBLIC  QtXlsxWriter)
