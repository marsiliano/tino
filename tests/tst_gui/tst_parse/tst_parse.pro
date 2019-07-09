TINO_LIB_DEPENDS += \
    core \
    yaml \
    gui

INCLUDEPATH += $$PWD/../../../src/yaml/yaml-cpp/include

include(../../test.pri)

SOURCES += tst_Parse.cpp
