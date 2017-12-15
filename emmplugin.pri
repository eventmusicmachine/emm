include($$replace(_PRO_FILE_PWD_, (emm-plugin-)?([^/]+)$, \\1\\2/\\2_dependencies.pri))
TARGET = $$qtLibraryTarget($$EMM_PLUGIN_NAME)

include(emm.pri)

include(rpath.pri)

TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$EMM_PLUGIN_PATH
