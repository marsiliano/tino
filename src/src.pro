TEMPLATE  = subdirs
CONFIG   += ordered
QMAKE_LFLAGS += $$QMAKE_LFLAGS_NOUNDEF
SUBDIRS += \
    json \
    core \
    connector \
    widget \
    gui \
    app
