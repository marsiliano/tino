TEMPLATE = subdirs
SUBDIRS += 3rd-party src app tests
3rd-party.subdir = app/3rd-party
src.subdir = app/src
src.depends = 3rd-party
app.depends = src
tests.depends = src
