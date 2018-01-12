include(../../emmplugin.pri)

DEFINES += AUDIO_LIBRARY

QT += widgets

SOURCES += \
    audioplugin.cpp \
    outputselectionwidget.cpp \
    devicemanager.cpp \
    idriver.cpp \
    audiosettingspage.cpp

HEADERS += \
    audioplugin.h \
    audio_global.h \
    outputselectionwidget.h \
    devicemanager.h \
    devicemanager_p.h \
    idriver.h \
    idevice.h \
    ichannel.h \
    audiosettingsfactory.h \
    audiosettingspage.h

FORMS += \
    outputselectionwidget.ui \
    audiosettingspage.ui

DISTFILES += \
    audio.json
