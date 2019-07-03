include($$PWD/../tino.pri)

isEmpty(TEMPLATE):TEMPLATE = app
QT += testlib
CONFIG += qt warn_on console depend_includepath testcase
CONFIG -= app_bundle
