TEMPLATE = lib
TARGET = src
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

include($$PWD/../3rd-party/yaml-cpp/yaml-cpp.pri)

FORMS += \
    MainWindow.ui

HEADERS += \
    MainWindow.hpp

SOURCES += \
    MainWindow.cpp
