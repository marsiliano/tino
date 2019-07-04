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

FORMS += \
    MainWindow.ui

HEADERS += \
    MainWindow.hpp \
Byte.hpp \
Block.hpp \
Group.hpp \

SOURCES += \
    MainWindow.cpp \
Byte.cpp \
Block.cpp  \
Group.cpp \
