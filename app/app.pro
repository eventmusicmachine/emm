include(../emm.pri)

TEMPLATE = app
TARGET = $$EMM_APP_TARGET
DESTDIR = $$EMM_APP_PATH
VERSION = $$EMM_VERSION
QT -= testlib
QT += widgets

LIBS += -lExtensionSystem -lUtils

DEFINES += EMM_VERSION=\\\"$$EMM_VERSION\\\"
DEFINES += RELATIVE_PLUGIN_PATH_STR=\\\"$$RELATIVE_PLUGIN_PATH\\\"

SOURCES += main.cpp \
    application.cpp

HEADERS += \
    application.h \
    app_version.h
