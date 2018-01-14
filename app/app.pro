include(../emm.pri)

TEMPLATE = app
TARGET = $$EMM_APP_TARGET
DESTDIR = $$EMM_APP_PATH
VERSION = $$EMM_VERSION
QT -= testlib
QT += widgets

LIBS += -l$$qtLibraryName(ExtensionSystem, 4.5.0) -l$$qtLibraryName(Utils, 4.5.0)

DEFINES += EMM_VERSION=\\\"$$EMM_VERSION\\\"

SOURCES += main.cpp

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    app.rc

win32 {
    DEFINES += RC_VERSION=$$replace(EMM_VERSION, "\\.", ","),0 \
        RC_VERSION_STRING=\"$${EMM_DISPLAY_VERSION}\"
    RC_FILE = app.rc
}
