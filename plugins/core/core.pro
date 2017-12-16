include(../../emmplugin.pri)

DEFINES += CORE_LIBRARY

QT += widgets
LIBS += -l$$qtLibraryName(ExtensionSystem, 4.5.0)

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
    icore.h \
    icentralcomponentfactory.h

DISTFILES += \
    core.json

FORMS += \
    aboutdialog.ui


