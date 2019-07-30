include(../tinolibrary.pri)

INCLUDEPATH += "../json/rapidjson/include/"

HEADERS += \
    $$PWD/Byte.hpp \
    $$PWD/Block.hpp \
    $$PWD/Group.hpp \
    $$PWD/Generator.hpp \
    $$PWD/Parser.hpp \
    $$PWD/Settings.hpp \

SOURCES += \
    $$PWD/Byte.cpp \
    $$PWD/Block.cpp \
    $$PWD/Group.cpp \
    $$PWD/Generator.cpp \
    $$PWD/Parser.cpp \
    $$PWD/Settings.cpp \
