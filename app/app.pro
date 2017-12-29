include(../emm.pri)

TEMPLATE = app
TARGET = $$EMM_APP_TARGET
DESTDIR = $$EMM_APP_PATH
VERSION = $$EMM_VERSION
QT -= testlib
QT += widgets

LIBS += -l$$qtLibraryName(ExtensionSystem, 4.5.0) -l$$qtLibraryName(Utils, 4.5.0)

DEFINES += EMM_VERSION=\\\"$$EMM_VERSION\\\"
DEFINES += RELATIVE_PLUGIN_PATH_STR=\\\"$$RELATIVE_PLUGIN_PATH\\\"

SOURCES += main.cpp

RESOURCES += \
    resources.qrc
