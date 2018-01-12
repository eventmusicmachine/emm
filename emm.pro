include(emm.pri)

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    libs \
    app \
    plugins \
    test

OTHER_FILES += \
    README.md \
    LICENSE \
    .gitignore \
    .travis.yml
