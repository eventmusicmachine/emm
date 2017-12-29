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
    $$PWD/include/cartslot.h \
    $$PWD/include/cartslotwidget.h \
    $$PWD/include/editcartslotdialog.h \
    $$PWD/include/loadslotdialog.h \
    $$PWD/include/slottablemodel.h \
    $$PWD/include/clearlayerthread.h \
    $$PWD/include/copycolorsthread.h

SOURCES += \
    $$PWD/src/cartslot.cpp \
    $$PWD/src/cartslotwidget.cpp \
    $$PWD/src/editcartslotdialog.cpp \
    $$PWD/src/loadslotdialog.cpp \
    $$PWD/src/slottablemodel.cpp \
    $$PWD/src/clearlayerthread.cpp \
    $$PWD/src/copycolorsthread.cpp

FORMS += \
    $$PWD/ui/cartslotwidget.ui \
    $$PWD/ui/editcartslotdialog.ui \
    $$PWD/ui/loadslotdialog.ui

TRANSLATIONS = \
    $$PWD/translations/emm_slots_en.ts \
    $$PWD/translations/emm_slots_de.ts

RESOURCES += \
    $$PWD/resources/icons.qrc
