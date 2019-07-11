include(../tinolibrary.pri)

QT += core gui widgets

INCLUDEPATH += $$PWD/../yaml/yaml-cpp/include

FORMS += \
    $$PWD/MainWindow.ui \

HEADERS += \
    $$PWD/MainWindow.hpp \

SOURCES += \
    $$PWD/MainWindow.cpp \
