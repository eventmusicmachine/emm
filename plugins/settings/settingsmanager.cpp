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

#include <QLoggingCategory>

#include "settingsmanager.h"
#include "settingsmanager_p.h"
#include "navigationtreeitem_p.h"

Q_LOGGING_CATEGORY(settingsManagerLog, "emm.settingsmanager")

using namespace Settings;
using namespace Settings::Internal;

static SettingsManager *m_instance = 0;
static SettingsManagerPrivate *d;

SettingsManager::SettingsManager(QObject *parent) : QObject(parent)
{
    m_instance = this;
    d = new SettingsManagerPrivate;
    SettingsManager::createNavigationNode("ROOT", "ROOT");
}

SettingsManager::~SettingsManager()
{
    delete d;
}

SettingsManager *SettingsManager::instance()
{
    return m_instance;
}

NavigationTreeItem *SettingsManager::createNavigationNode(QString id, QString text)
{
    NavigationTreeItemPrivate *item = new NavigationTreeItemPrivate(id, text);
    d->m_idNodeMap.insert(id, item);
    return item;
}

NavigationTreeItem *SettingsManager::navigationNode(QString id)
{
    const SettingsManagerPrivate::IdNavigationNodeMap::const_iterator it = d->m_idNodeMap.constFind(id);
    if (it == d->m_idNodeMap.constEnd()) {
        qCWarning(settingsManagerLog) << "SettingsManager::navigationNode(): failed to find :" << id;
        return 0;
    }
    return it.value();
}

SettingsManagerPrivate::~SettingsManagerPrivate()
{
    qDeleteAll(m_idNodeMap);
}
