include(../../emmplugin.pri)

DEFINES += CORE_LIBRARY

QT += widgets
LIBS += -l$$qtLibraryName(ExtensionSystem, 4.5.0)

SOURCES += \
    mainwindow.cpp \
    aboutdialog.cpp \
    icore.cpp \
    coreplugin.cpp

HEADERS += \
    core_global.h \
    mainwindow.h \
    aboutdialog.h \
    icore.h \
    icentralcomponentfactory.h \
    coreplugin.h

DISTFILES += \
    core.json

FORMS += \
    aboutdialog.ui


