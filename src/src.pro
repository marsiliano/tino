TEMPLATE  = subdirs
CONFIG   += ordered
QMAKE_LFLAGS += $$QMAKE_LFLAGS_NOUNDEF
SUBDIRS +=  \
    core    \
    parser  \
    gui     \
    app
