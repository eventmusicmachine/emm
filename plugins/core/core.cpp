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

#include "core.h"
#include "mainwindow.h"
#include "actionmanager/actionmanager.h"

using namespace Core;
using namespace Core::Internal;
using namespace Actions;

CorePlugin::CorePlugin() : m_mainWindow(0)
{
}

CorePlugin::~CorePlugin()
{
    delete m_mainWindow;
}

bool CorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage)

    ActionManager::initialize(this);
    m_mainWindow = new MainWindow;
    const bool success = m_mainWindow->init(errorMessage);

    return success;
}

void CorePlugin::extensionsInitialized()
{
    m_mainWindow->extensionsInitialized();
}
