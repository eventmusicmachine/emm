include(../../emmplugin.pri)

DEFINES += SETTINGS_LIBRARY

QT += widgets

SOURCES += \
    settingsdialog.cpp \
    navigationtreemodel.cpp \
    navigationtreeitem.cpp \
    settingsmanager.cpp \
    settingsplugin.cpp

HEADERS += \
    settings_global.h \
    settingsdialog.h \
    navigationtreemodel.h \
    navigationtreeitem.h \
    settingsmanager.h \
    settingsmanager_p.h \
    settingsplugin.h \
    navigationtreeitem_p.h \
    isettingspagefactory.h \
    isettingspage.h

DISTFILES += \
    settings.json

FORMS += \
    settingsdialog.ui
