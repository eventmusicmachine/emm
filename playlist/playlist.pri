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

INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/include/historylistwidget.h \
    $$PWD/include/lst.h \
    $$PWD/include/m3u.h \
    $$PWD/include/playlist.h \
    $$PWD/include/playlistentry.h \
    $$PWD/include/playlistwidget.h \
    $$PWD/include/playlistplayer.h \
    $$PWD/include/rowmovetablewidget.h \
    $$PWD/include/editplayerdialog.h \
    $$PWD/include/playerwidget.h

SOURCES += \
    $$PWD/src/historylistwidget.cpp \
    $$PWD/src/lst.cpp \
    $$PWD/src/m3u.cpp \
    $$PWD/src/playlist.cpp \
    $$PWD/src/playlistentry.cpp \
    $$PWD/src/playlistwidget.cpp \
    $$PWD/src/playlistplayer.cpp \
    $$PWD/src/rowmovetablewidget.cpp \
    $$PWD/src/editplayerdialog.cpp \
    $$PWD/src/playerwidget.cpp

TRANSLATIONS = \
    $$PWD/translations/emm_playlist_en.ts \
    $$PWD/translations/emm_playlist_de.ts

FORMS += \
    $$PWD/ui/editplayerdialog.ui \
    $$PWD/ui/playerwidget.ui

RESOURCES += \
    $$PWD/resources/icons.qrc
