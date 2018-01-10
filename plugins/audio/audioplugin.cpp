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

#include <settings/settingsmanager.h>
#include <settings/navigationtreeitem.h>

#include "audioplugin.h"
#include "devicemanager.h"
#include "audiosettingsfactory.h"

using namespace Audio;
using namespace Audio::Internal;

AudioPlugin::AudioPlugin()
{
}

AudioPlugin::~AudioPlugin()
{

}

bool AudioPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    new DeviceManager(this);

    Settings::NavigationTreeItem *settingsItem = Settings::SettingsManager::createNavigationNode("AUDIO", tr("Audio"));
    settingsItem->setFactory(new AudioSettingsFactory());
    Settings::SettingsManager::navigationNode("ROOT")->addChild(settingsItem);

    return true;
}

void AudioPlugin::extensionsInitialized()
{
}

ExtensionSystem::IPlugin::ShutdownFlag AudioPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
