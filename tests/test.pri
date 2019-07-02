isEmpty(TEMPLATE):TEMPLATE = app
QT += testlib core gui widgets

CONFIG += qt warn_on console depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH *= $$PWD/../app/src/

LIBS += -L$$shadowed($$PWD)/../app/src/ -lsrc
