TEMPLATE = app
TARGET = tino
CONFIG += c++17

QT += core gui widgets

CONFIG(release, debug|release) {
    QMAKE_CXXFLAGS += -O3
}

CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += -O0
    QMAKE_CXXFLAGS -= -O1
    QMAKE_CXXFLAGS -= -O2
    QMAKE_CXXFLAGS -= -O3
    QMAKE_CXXFLAGS += --debug
}

LIBS += -L$$shadowed($$PWD)/src/ -lsrc

INCLUDEPATH += $$PWD/src/

SOURCES += $$PWD/main.cpp
