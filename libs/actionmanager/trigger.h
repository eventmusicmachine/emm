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

#ifndef TRIGGER_H
#define TRIGGER_H

#include <QObject>

#include "actionmanager_global.h"

namespace Actions {

class Action;
class Signal;

namespace Internal {

class TriggerPrivate;

} // namespace Internal

class ACTIONMANAGER_EXPORT Trigger : public QObject
{
    Q_OBJECT
public:
    Trigger(QObject *parent = 0);

    virtual Signal* createSignal(QString id, QString description) = 0;
    Signal* signal(QString id) const;

protected:
    Trigger(Internal::TriggerPrivate &d);
    Internal::TriggerPrivate *d;
};

} // namespace Actions

#endif // TRIGGER_H
