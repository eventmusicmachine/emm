DEFINES += ACTIONMANAGER_LIBRARY
include(../../emmlibrary.pri)

QT += widgets

SOURCES += \
    actionmanager.cpp \
    actioncontainer.cpp \
    action.cpp

HEADERS += \
    actionmanager.h \
    actionmanager_global.h \
    actionmanager_p.h \
    actioncontainer.h \
    actioncontainer_p.h \
    action.h \
    action_p.h
