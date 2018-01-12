include($$replace(_PRO_FILE_PWD_, (emm-plugin-)?([^/]+)$, \\1\\2/\\2_dependencies.pri))
TARGET = $$qtLibraryTarget($$EMM_PLUGIN_NAME)

include(emm.pri)

include(rpath.pri)

TEMPLATE = lib
CONFIG += plugin
LIBS += -l$$qtLibraryName(ExtensionSystem, 4.5.0)

DESTDIR = $$EMM_PLUGIN_PATH
