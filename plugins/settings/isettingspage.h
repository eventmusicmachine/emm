/**************************************************************************
 * Event Music Machine
 * Copyright (C) 2014-2017 Christoph Kraemer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************/

#ifndef ISETTINGSPAGE_H
#define ISETTINGSPAGE_H

#include <QObject>

#include "settings_global.h"

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

namespace Settings {

class SETTINGS_EXPORT ISettingsPage : public QObject
{
    Q_OBJECT
public:
    virtual QString id() const = 0;
    virtual QWidget *widget() = 0;

public:
    virtual void load() = 0;
    virtual void apply() = 0;
};

} //namespace Settings

#endif // ISETTINGSPAGE_H
