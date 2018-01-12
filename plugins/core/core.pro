include(../../emmplugin.pri)

DEFINES += CORE_LIBRARY

QT += widgets

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

FORMS += \
    aboutdialog.ui

DISTFILES += \
    core.json
