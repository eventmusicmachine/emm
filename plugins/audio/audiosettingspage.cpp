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

#include <QSettings>
#include <extensionsystem/pluginmanager.h>

#include "audiosettingspage.h"
#include "ui_audiosettingspage.h"

using namespace Audio::Internal;

AudioSettingsPage::AudioSettingsPage() :
    Settings::ISettingsPage(),
    m_ui(new Ui::AudioSettingsPage)
{
    m_ui->setupUi(this);
}

AudioSettingsPage::~AudioSettingsPage()
{
    delete m_ui;
}

QString AudioSettingsPage::id() const
{
    return "AudioGeneralSettings";
}

void AudioSettingsPage::apply()
{
    QSettings *settings = ExtensionSystem::PluginManager::instance()->settings();
    settings->beginGroup("pfl");
    settings->setValue("driver", m_ui->pflOutputWidget->driver());
    settings->setValue("device", m_ui->pflOutputWidget->device());
    settings->setValue("output", m_ui->pflOutputWidget->channel());
    settings->endGroup();
}

void AudioSettingsPage::load()
{
    QSettings *settings = ExtensionSystem::PluginManager::instance()->settings();
    settings->beginGroup("pfl");
    QString driver = settings->value("driver", "").toString();
    int device = settings->value("device", 1).toInt();
    int output = settings->value("output", 1).toInt();
    settings->endGroup();

    m_ui->pflOutputWidget->setSelection(driver, device, output);
}
