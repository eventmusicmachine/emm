include(../../emmplugin.pri)

DEFINES += AUDIO_LIBRARY

LIBS += -l$$qtLibraryName(ExtensionSystem, 4.5.0)

SOURCES += \
    audioplugin.cpp

HEADERS += \
    audioplugin.h \
    audio_global.h

DISTFILES += \
    audio.json
