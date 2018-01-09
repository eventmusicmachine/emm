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

#include "devicemanager.h"
#include "devicemanager_p.h"
#include "idriver.h"

using namespace Audio;
using namespace Audio::Internal;

static DeviceManager *m_instance = 0;
static DeviceManagerPrivate *d;

DeviceManager::DeviceManager(QObject *parent) : QObject(parent)
{
    m_instance = this;
    d = new DeviceManagerPrivate;
}

DeviceManager::~DeviceManager()
{
    delete d;
}

DeviceManager *DeviceManager::instance()
{
    return m_instance;
}

QMap<QString, IDriver*> DeviceManager::drivers()
{
    return d->m_drivers;
}

void DeviceManager::registerDriver(IDriver *driver)
{
    d->m_drivers.insert(driver->id(), driver);
}

DeviceManagerPrivate::~DeviceManagerPrivate()
{
    qDeleteAll(m_drivers);
}
