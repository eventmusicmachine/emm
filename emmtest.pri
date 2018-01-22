include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))
TARGET = $$EMM_TEST_NAME

include(emm.pri)

include(rpath.pri)

QT += testlib

TEMPLATE = app

DESTDIR = $$EMM_APP_PATH
