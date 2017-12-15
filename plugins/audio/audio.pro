include(../../emmplugin.pri)

DEFINES += AUDIO_LIBRARY

LIBS += -lExtensionSystem

SOURCES += \
    audioplugin.cpp

HEADERS += \
    audioplugin.h \
    audio_global.h

DISTFILES += \
    audio.json
