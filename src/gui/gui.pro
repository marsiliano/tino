include(../tinolibrary.pri)

FORMS += \
    $$PWD/MainWindow.ui \
    $$PWD/DialogAbout.ui

HEADERS += \
    $$PWD/MainWindow.hpp \
    $$PWD/DialogAbout.hpp \
    $$PWD/ConfigViewFactory.hpp

SOURCES += \
    $$PWD/MainWindow.cpp \
    $$PWD/DialogAbout.cpp \
    $$PWD/ConfigViewFactory.cpp
