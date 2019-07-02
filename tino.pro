TEMPLATE = subdirs
SUBDIRS += src app tests
src.subdir = app/src
app.depends = src
tests.depends = src
