include(../../emmplugin.pri)

DEFINES += SETTINGS_LIBRARY

QT += widgets
LIBS += -lExtensionSystem

SOURCES += \
        settings.cpp \
    settingsdialog.cpp

HEADERS += \
        settings.h \
        settings_global.h \ 
    settingsdialog.h

DISTFILES += \
    settings.json

FORMS += \
    settingsdialog.ui
