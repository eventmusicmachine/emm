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

#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QSettings>
#include <QStandardPaths>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>
#include <utils/hostosinfo.h>

#include "application.h"
#include "app_version.h"

using namespace ExtensionSystem;

const char corePluginName[] = "Core";

typedef QList<PluginSpec *> PluginSpecSet;

static void displayError(const QString &t)
{
    if (Utils::HostOsInfo::isWindowsHost()) {
        QMessageBox::critical(0, QLatin1String('Event Music Machine'), t);
    } else {
        qCritical("%s", qPrintable(t));
    }
}

static inline QString msgCoreLoadFailure(const QString &why)
{
    return QCoreApplication::translate("Application", "Failed to load core: %1").arg(why);
}

static inline QStringList getPluginPaths()
{
    QStringList rc(QDir::cleanPath(QApplication::applicationDirPath() + '/' + Core::Constants::RELATIVE_PLUGIN_PATH));
    // Local plugin path: <localappdata>/plugins/<ideversion>
    //    where <localappdata> is e.g.
    //    "%LOCALAPPDATA%\EMM\emm" on Windows Vista and later
    //    "$XDG_DATA_HOME/data/EMM/emm" or "~/.local/share/data/EMM/emm" on Linux
    //    "~/Library/Application Support/EMM/Event Music Machine" on Mac
    QString pluginPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    if (Utils::HostOsInfo::isAnyUnixHost() && !Utils::HostOsInfo::isMacHost()) {
        pluginPath += QLatin1String("/data");
    }
    pluginPath += QLatin1Char('/') + QLatin1String('EMM') + QLatin1Char('/');
    pluginPath += QLatin1String(Utils::HostOsInfo::isMacHost() ? "Event Music Machine" : "EMM");
    pluginPath += QLatin1String("/plugins/");
    pluginPath += QLatin1String(Core::Constants::EMM_VERSION_LONG);
    rc.push_back(pluginPath);
    return rc;
}

int main(int argc, char *argv[])
{
    Core::Application app((QLatin1String("Event Music Machine")), argc, argv);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings *settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "EMM", "emm");
    
    PluginManager pluginManager;
    PluginManager::setPluginIID(QLatin1String("de.eventmusicmachine.EmmPlugin"));
    PluginManager::setSettings(settings);

    // Load
    const QStringList pluginPaths = getPluginPaths();
    PluginManager::setPluginPaths(pluginPaths);

    const PluginSpecSet plugins = PluginManager::plugins();
    PluginSpec *coreplugin = 0;
    foreach (PluginSpec *spec, plugins) {
        if (spec->name() == QLatin1String(corePluginName)) {
            coreplugin = spec;
            break;
        }
    }
    if (!coreplugin) {
        QString nativePaths = QDir::toNativeSeparators(pluginPaths.join(QLatin1Char(',')));
        const QString reason = QCoreApplication::translate("Application", "Could not find Core plugin in %1").arg(nativePaths);
        displayError(msgCoreLoadFailure(reason));
        return 1;
    }
    if (!coreplugin->isEffectivelyEnabled()) {
        const QString reason = QCoreApplication::translate("Application", "Core plugin is disabled.");
        displayError(msgCoreLoadFailure(reason));
        return 1;
    }
    if (coreplugin->hasError()) {
        displayError(msgCoreLoadFailure(coreplugin->errorString()));
        return 1;
    }

    PluginManager::loadPlugins();
    if (coreplugin->hasError()) {
        displayError(msgCoreLoadFailure(coreplugin->errorString()));
        return 1;
    }

    // shutdown plugin manager on the exit
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &pluginManager, &PluginManager::shutdown);

    return app.exec();
}
