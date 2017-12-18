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
#include <actionmanager/actionmanager.h>
#include <actionmanager/actioncontainer.h>
#include <actionmanager/action.h>
#include <core/icore.h>

#include "settingsplugin.h"
#include "settingsdialog.h"
#include "settingsmanager.h"

using namespace Settings::Internal;

SettingsPlugin::SettingsPlugin()
{

}

SettingsPlugin::~SettingsPlugin()
{

}

bool SettingsPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage)

    new SettingsManager(this);

    Actions::ActionContainer *fileMenu = Actions::ActionManager::actionContainer("FILE_MENU");

    QAction *settingsAction = new QAction(tr("Settings..."), this);
    settingsAction->setMenuRole(QAction::PreferencesRole);
    Actions::Action *a = Actions::ActionManager::registerAction(settingsAction, "SETTINGS");
    fileMenu->addAction(a);
    connect(settingsAction, &QAction::triggered, this, &SettingsPlugin::showSettingsDialog);
    return true;
}

void SettingsPlugin::extensionsInitialized()
{

}

bool SettingsPlugin::delayedInitialize()
{
    return true;
}

void SettingsPlugin::showSettingsDialog()
{
    SettingsDialog settingsDialog(Core::ICore::dialogParent());
    settingsDialog.exec();
}
