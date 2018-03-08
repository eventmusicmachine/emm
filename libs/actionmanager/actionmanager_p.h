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

#ifndef ACTIONMANAGER_P_H
#define ACTIONMANAGER_P_H

#include <QObject>
#include <QHash>

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

namespace Actions {

class ActionManager;
class Trigger;
class Receiver;

namespace Internal {

class ActionContainerPrivate;
class ActionPrivate;

class ActionManagerPrivate : public QObject
{
    Q_OBJECT

public:
    typedef QHash<QString, ActionContainerPrivate *> IdContainerMap;
    typedef QHash<QString, ActionPrivate *> IdActionMap;
    typedef QHash<QString, Trigger *> IdTriggerMap;
    typedef QHash<QString, Receiver *> IdReceiverMap;

    ~ActionManagerPrivate();

    ActionPrivate *createAction(QAction *Action, QString id);

    IdContainerMap m_idContainerMap;
    IdActionMap m_idActionMap;
    IdTriggerMap m_idTriggerMap;
    IdReceiverMap m_idReceiverMap;
};

} // namespace Internal
} // namespace Actions

#endif // ACTIONMANAGER_P_H
