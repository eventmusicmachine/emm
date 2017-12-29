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

win32 {
    LIBS += -L$$PWD/lib/win
}
macx {
    LIBS += -L$$PWD/lib/mac
}
LIBS += -lbass -ltags -lbassmix -lbass_fx

INCLUDEPATH += $$PWD/lib/header
INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/include/abstractaudioobject.h \
    $$PWD/include/abstractbassdevice.h \
    # $$PWD/include/bassasiodevice.h \
    $$PWD/include/bassdevice.h \
    $$PWD/include/audioprocessor.h \
    $$PWD/include/pflplayer.h \
    $$PWD/include/pluginloader.h \
    $$PWD/include/audiovisualizer.h \
    $$PWD/include/deviceselectwidget.h

SOURCES += \
    $$PWD/src/abstractaudioobject.cpp \
    $$PWD/src/abstractbassdevice.cpp \
    # $$PWD/src/bassasiodevice.cpp \
    $$PWD/src/bassdevice.cpp \
    $$PWD/src/audioprocessor.cpp \
    $$PWD/src/pflplayer.cpp \
    $$PWD/src/pluginloader.cpp \
    $$PWD/src/audiovisualizer.cpp \
    $$PWD/src/deviceselectwidget.cpp

FORMS += \
    $$PWD/ui/deviceselectwidget.ui

TRANSLATIONS = \
    $$PWD/translations/emm_audio_en.ts \
    $$PWD/translations/emm_audio_de.ts
