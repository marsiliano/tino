TEMPLATE  = subdirs
CONFIG   += ordered
QMAKE_LFLAGS += $$QMAKE_LFLAGS_NOUNDEF
SUBDIRS += \
    core \
#    connector \
#    widget \
    gui \
    app
