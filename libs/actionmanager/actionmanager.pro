DEFINES += ACTIONMANAGER_LIBRARY
include(../../emmlibrary.pri)

QT += widgets

SOURCES += \
    actionmanager.cpp \
    actioncontainer.cpp \
    action.cpp \
    trigger.cpp \
    mousetrigger.cpp \
    mousesignal.cpp \
    signal.cpp

HEADERS += \
    actionmanager.h \
    actionmanager_global.h \
    actionmanager_p.h \
    actioncontainer.h \
    actioncontainer_p.h \
    action.h \
    action_p.h \
    trigger.h \
    mousetrigger.h \
    mousesignal.h \
    signal.h \
    signal_p.h \
    mousesignal_p.h
