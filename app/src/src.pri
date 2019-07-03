include($$PWD/../3rd-party/yaml-cpp/yaml-cpp.pri)

LIBS += -L$$shadowed($$PWD)/ -lsrc

INCLUDEPATH += $$PWD/

