include(emm.pri)

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    libs \
    app \
    plugins

OTHER_FILES += \
    README.md \
    LICENSE \
    .gitignore
