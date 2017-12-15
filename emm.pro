include(emm.pri)

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    libs \
    app \
    plugins

DISTFILES += \
    README.md \
    LICENSE
