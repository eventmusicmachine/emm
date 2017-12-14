include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))

TARGET = $$qtLibraryTarget($$EMM_PLUGIN_NAME)

include(emm.pri)

include(rpath.pri)

TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$EMM_PLUGIN_PATH
