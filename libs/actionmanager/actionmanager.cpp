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

#include <QAction>
#include <QLoggingCategory>
#include <QMenuBar>

#include "actionmanager.h"
#include "actionmanager_p.h"
#include "actioncontainer_p.h"
#include "action_p.h"
#include "trigger.h"
#include "receiver.h"
#include "signal.h"

Q_LOGGING_CATEGORY(actionManagerLog, "emm.actionmanager")

using namespace Actions;
using namespace Actions::Internal;

static ActionManager *m_instance = 0;
static ActionManagerPrivate *d;
static bool m_initialized = false;

ActionManager::ActionManager(QObject *parent) : QObject(parent)
{
    m_instance = this;
    d = new ActionManagerPrivate;
}

ActionManager::~ActionManager()
{
    delete d;
}

void ActionManager::initialize(QObject *parent)
{
    if (m_initialized) {
        return;
    }
    new ActionManager(parent);
    m_initialized = true;
}

ActionManager* ActionManager::instance()
{
    return m_instance;
}

ActionContainer *ActionManager::createMenu(QString id)
{
    MenuActionContainer *mc = new MenuActionContainer(id);

    d->m_idContainerMap.insert(id, mc);

    return mc;
}

ActionContainer *ActionManager::createMenuBar(QString id)
{
    MenuBarActionContainer *mbc = new MenuBarActionContainer(id);

    d->m_idContainerMap.insert(id, mbc);

    return mbc;
}

Action *ActionManager::registerAction(QAction *action, QString id)
{
    Action *a = d->createAction(action, id);

    return a;
}

Trigger *ActionManager::registerTrigger(QString id, Trigger *trigger)
{
    d->m_idTriggerMap.insert(id, trigger);
    return trigger;
}

Receiver *ActionManager::registerReceiver(QString id, Receiver *receiver)
{
    d->m_idReceiverMap.insert(id, receiver);
    return receiver;
}

ActionContainer *ActionManager::actionContainer(QString id)
{
    const ActionManagerPrivate::IdContainerMap::const_iterator it = d->m_idContainerMap.constFind(id);
    if (it == d->m_idContainerMap.constEnd()) {
        qCWarning(actionManagerLog) << "ActionManagerPrivate::actionContainer(): failed to find :" << id;
        return 0;
    }
    return it.value();
}

ActionManagerPrivate::~ActionManagerPrivate()
{
    qDeleteAll(m_idContainerMap);
    qDeleteAll(m_idTriggerMap);
    qDeleteAll(m_idReceiverMap);
}

ActionPrivate *ActionManagerPrivate::createAction(QAction *action, QString id)
{
    ActionPrivate *a  = m_idActionMap.value(id, 0);

    if (!a) {
        a = new ActionPrivate(id, action);
        m_idActionMap.insert(id, a);
    }

    return a;
}
