include(../tinolibrary.pri)

QT += core gui widgets

HEADERS += \
    $$PWD/BtnContainer.hpp \
    $$PWD/Mask.hpp \
    $$PWD/Value.hpp \
    $$PWD/Joined.hpp \
    $$PWD/GroupWidget.hpp \
    $$PWD/BlockWidget.hpp \
    $$PWD/ScrollBlock.hpp

SOURCES += \
    $$PWD/BtnContainer.cpp \
    $$PWD/Mask.cpp \
    $$PWD/Value.cpp \
    $$PWD/Joined.cpp \
    $$PWD/GroupWidget.cpp \
    $$PWD/BlockWidget.cpp \
    $$PWD/ScrollBlock.cpp
