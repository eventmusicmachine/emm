!isEmpty(EMM_PRI_INCLUDED):error("emm.pri already included")
EMM_PRI_INCLUDED = 1

EMM_VERSION = 3.0.0
VERSION = $$EMM_VERSION

isEmpty(EMM_LIBRARY_BASENAME) {
    EMM_LIBRARY_BASENAME = lib
}

EMM_SOURCE_TREE = $$PWD
isEmpty(EMM_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    EMM_BUILD_TREE = $$clean_path($$OUT_PWD)
    EMM_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

EMM_APP_PATH = $$EMM_BUILD_TREE/bin
osx {
    EMM_APP_TARGET = "Event Music Machine"

    exists($$EMM_BUILD_TREE/Contents/MacOS/Event Music Machine): EMM_APP_BUNDLE = $$EMM_BUILD_TREE
    else: EMM_APP_BUNDLE = $$EMM_APP_PATH/$${EMM_APP_TARGET}.app

    isEmpty(EMM_OUTPUT_PATH): EMM_OUTPUT_PATH = $$EMM_APP_BUNDLE/Contents

    EMM_LIBRARY_PATH = $$EMM_OUTPUT_PATH/Frameworks
    EMM_PLUGIN_PATH  = $$EMM_OUTPUT_PATH/PlugIns
    EMM_BIN_PATH     = $$EMM_OUTPUT_PATH/MacOS

    LINK_LIBRARY_PATH = $$EMM_APP_BUNDLE/Contents/Frameworks
    LINK_PLUGIN_PATH  = $$EMM_APP_BUNDLE/Contents/PlugIns
} else {
    EMM_APP_TARGET = "emm"

    isEmpty(EMM_OUTPUT_PATH): EMM_OUTPUT_PATH = $$EMM_BUILD_TREE

    EMM_LIBRARY_PATH = $$EMM_OUTPUT_PATH/$$EMM_LIBRARY_BASENAME/emm
    EMM_PLUGIN_PATH  = $$EMM_LIBRARY_PATH/plugins
    EMM_BIN_PATH     = $$EMM_OUTPUT_PATH/bin

    LINK_LIBRARY_PATH = $$EMM_BUILD_TREE/$$EMM_LIBRARY_BASENAME/emm
    LINK_PLUGIN_PATH  = $$LINK_LIBRARY_PATH/plugins
}

RELATIVE_PLUGIN_PATH = $$relative_path($$EMM_PLUGIN_PATH, $$EMM_BIN_PATH)

INCLUDEPATH += \
    $$EMM_SOURCE_TREE/libs \
    $$EMM_SOURCE_TREE/headers

LIBS *= -L$$LINK_LIBRARY_PATH -L$$EMM_SOURCE_TREE/external

EMM_PLUGIN_DIRS += $$EMM_SOURCE_TREE/plugins
for(dir, EMM_PLUGIN_DIRS) {
    INCLUDEPATH += $$dir
}

!isEmpty(EMM_PLUGIN_DEPENDS) {
    LIBS *= -L$$EMM_PLUGIN_PATH
    LIBS *= -L$$LINK_PLUGIN_PATH
}

# recursively resolve plugin deps
done_plugins =
for(ever) {
    isEmpty(EMM_PLUGIN_DEPENDS): \
        break()
    done_plugins += $$EMM_PLUGIN_DEPENDS
    for(dep, EMM_PLUGIN_DEPENDS) {
        dependencies_file =
        for(dir, EMM_PLUGIN_DIRS) {
            exists($$dir/$$dep/$${dep}_dependencies.pri) {
                dependencies_file = $$dir/$$dep/$${dep}_dependencies.pri
                break()
            }
        }
        isEmpty(dependencies_file): \
            error("Plugin dependency $$dep not found")
        include($$dependencies_file)
        LIBS += -l$$EMM_PLUGIN_NAME
    }
    EMM_PLUGIN_DEPENDS = $$unique(EMM_PLUGIN_DEPENDS)
    EMM_PLUGIN_DEPENDS -= $$unique(done_plugins)
}

# recursively resolve library deps
done_libs =
for(ever) {
    isEmpty(EMM_LIB_DEPENDS): \
        break()
    done_libs += $$EMM_LIB_DEPENDS
    for(dep, EMM_LIB_DEPENDS) {
        include($$PWD/libs/$$dep/$${dep}_dependencies.pri)
        LIBS *= -l$$EMM_LIB_NAME
    }
    EMM_LIB_DEPENDS = $$unique(EMM_LIB_DEPENDS)
    EMM_LIB_DEPENDS -= $$unique(done_libs)
}
