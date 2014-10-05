# ----------------------------------------------------------------------------
# This file is part of Event Music Machine.
#
# Event Music Machine is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Event Music Machine is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Event Music Machine. If not, see <http://www.gnu.org/licenses/>.
# ----------------------------------------------------------------------------

QT += core gui widgets

TARGET = EventMusicMachine
TEMPLATE = app
CONFIG += x86

DESTDIR = bin
MOC_DIR += moc
RCC_DIR += rcc
UI_DIR += ui
OBJECTS_DIR += o

INCLUDEPATH += $$PWD/include

RC_FILE = $$PWD/resources/emm.rc

HEADERS += \
    $$PWD/include/aboutdialog.h \
    $$PWD/include/mainwindow.h \
    $$PWD/include/splashscreen.h

SOURCES += \
    $$PWD/src/aboutdialog.cpp \
    $$PWD/src/mainwindow.cpp \
    $$PWD/src/splashscreen.cpp \
    $$PWD/src/main.cpp

FORMS += \
    $$PWD/ui/aboutdialog.ui \
    $$PWD/ui/mainwindow.ui

TRANSLATIONS = \
    $$PWD/translations/emm_app_en.ts \
    $$PWD/translations/emm_app_de.ts

OTHER_FILES += \
    $$PWD/resources/emm.rc

RESOURCES += \
    $$PWD/resources/icons.qrc

include(../audio/audio.pri)
include(../slots/slots.pri)
include(../playlist/playlist.pri)
include(../settings/settings.pri)
include(../slotstore/slotstore.pri)
include(../widgets/widgets.pri)
include(../keyboard/keyboard.pri)
