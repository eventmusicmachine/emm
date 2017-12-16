include(../../emmplugin.pri)

DEFINES += SETTINGS_LIBRARY

QT += widgets
LIBS += -l$$qtLibraryName(ExtensionSystem, 4.5.0)

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
