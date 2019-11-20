include(../tinolibrary.pri)

FORMS += \
    $$PWD/MainWindow.ui \
    $$PWD/DialogAbout.ui \
    $$PWD/DialogSerialSettings.ui

HEADERS += \
    $$PWD/MainWindow.hpp \
    $$PWD/DialogAbout.hpp \
    $$PWD/ConfigViewFactory.hpp \
    $$PWD/DialogSerialSettings.hpp

SOURCES += \
    $$PWD/MainWindow.cpp \
    $$PWD/DialogAbout.cpp \
    $$PWD/ConfigViewFactory.cpp \
    $$PWD/DialogSerialSettings.cpp
