include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))
TARGET = $$qtLibraryTarget($$EMM_LIB_NAME)

include(emm.pri)

win32 {
    DLLDESTDIR = $$EMM_APP_PATH
}

DESTDIR = $$EMM_LIBRARY_PATH

include(rpath.pri)

TEMPLATE = lib
CONFIG += shared dll
