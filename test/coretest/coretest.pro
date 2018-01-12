include(../../emm.pri)

DESTDIR = $$EMM_APP_PATH
TEMPLATE = app
TARGET = CoreTests

QT += testlib

SOURCES +=  \
    main.cpp \
    testsuitetest.cpp

HEADERS += \
    testsuitetest.h
