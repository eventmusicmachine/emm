include(../../emmplugin.pri)

DEFINES += CORE_LIBRARY

QT += widgets
LIBS += -lExtensionSystem

SOURCES += \
    core.cpp \
    mainwindow.cpp \
    aboutdialog.cpp \
    icore.cpp

HEADERS += \
    core.h \
    core_global.h \
    mainwindow.h \
    aboutdialog.h \
    icore.h

DISTFILES += \
    core.json

FORMS += \
    aboutdialog.ui


