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


#ifndef MOUSETRIGGER_H
#define MOUSETRIGGER_H

#include "trigger.h"
#include "actionmanager_global.h"

namespace Actions {

class Action;

class ACTIONMANAGER_EXPORT MouseTrigger : public Trigger
{
    Q_OBJECT
public:
    MouseTrigger(QObject *parent = 0);

    Signal* createSignal(QString id, QString description) override;

signals:

public slots:
};

} // namespace Slots

#endif // MOUSETRIGGER_H
