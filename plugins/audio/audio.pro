include(../../emmplugin.pri)

DEFINES += AUDIO_LIBRARY

QT += widgets
LIBS += -l$$qtLibraryName(ExtensionSystem, 4.5.0)

SOURCES += \
    audioplugin.cpp \
    outputselectionwidget.cpp \
    devicemanager.cpp

HEADERS += \
    audioplugin.h \
    audio_global.h \
    outputselectionwidget.h \
    devicemanager.h \
    devicemanager_p.h \
    idriver.h \
    idevice.h

DISTFILES += \
    audio.json

FORMS += \
    outputselectionwidget.ui
