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
    // register all mime types from all plugins
    /* for (ExtensionSystem::PluginSpec *plugin : ExtensionSystem::PluginManager::plugins()) {
        if (!plugin->isEffectivelyEnabled())
            continue;
        const QJsonObject metaData = plugin->metaData();
        const QJsonValue mimetypes = metaData.value("Mimetypes");
        QString mimetypeString;
        if (Utils::readMultiLineString(mimetypes, &mimetypeString))
            Utils::addMimeTypes(plugin->name() + ".mimetypes", mimetypeString.trimmed().toUtf8());
    }

    if (ThemeEntry::availableThemes().isEmpty()) {
        *errorMessage = tr("No themes found in installation.");
        return false;
    }
    const CoreArguments args = parseArguments(arguments);
    Theme::initialPalette(); // Initialize palette before setting it
    Theme *themeFromArg = ThemeEntry::createTheme(args.themeId);
    setCreatorTheme(themeFromArg ? themeFromArg
                                 : ThemeEntry::createTheme(ThemeEntry::themeSetting()));
    new ActionManager(this);
    ActionManager::setPresentationModeEnabled(args.presentationMode);
    m_mainWindow = new MainWindow;
    if (args.overrideColor.isValid())
        m_mainWindow->setOverrideColor(args.overrideColor);
    m_locator = new Locator;
    qsrand(QDateTime::currentDateTime().toTime_t());
    const bool success = m_mainWindow->init(errorMessage);
    if (success) {
        m_editMode = new EditMode;
        addObject(m_editMode);
        ModeManager::activateMode(m_editMode->id());
        m_designMode = new DesignMode;
        InfoBar::initializeGloballySuppressed();
    }

    IWizardFactory::initialize();

    // Make sure we respect the process's umask when creating new files
    SaveFile::initializeUmask();

    Find::initialize();
    m_locator->initialize(this, arguments, errorMessage);

    MacroExpander *expander = Utils::globalMacroExpander();
    expander->registerVariable("CurrentDate:ISO", tr("The current date (ISO)."),
                               []() { return QDate::currentDate().toString(Qt::ISODate); });
    expander->registerVariable("CurrentTime:ISO", tr("The current time (ISO)."),
                               []() { return QTime::currentTime().toString(Qt::ISODate); });
    expander->registerVariable("CurrentDate:RFC", tr("The current date (RFC2822)."),
                               []() { return QDate::currentDate().toString(Qt::RFC2822Date); });
    expander->registerVariable("CurrentTime:RFC", tr("The current time (RFC2822)."),
                               []() { return QTime::currentTime().toString(Qt::RFC2822Date); });
    expander->registerVariable("CurrentDate:Locale", tr("The current date (Locale)."),
                               []() { return QDate::currentDate().toString(Qt::DefaultLocaleShortDate); });
    expander->registerVariable("CurrentTime:Locale", tr("The current time (Locale)."),
                               []() { return QTime::currentTime().toString(Qt::DefaultLocaleShortDate); });
    expander->registerVariable("Config:DefaultProjectDirectory", tr("The configured default directory for projects."),
                               []() { return DocumentManager::projectsDirectory().toString(); });
    expander->registerVariable("Config:LastFileDialogDirectory", tr("The directory last visited in a file dialog."),
                               []() { return DocumentManager::fileDialogLastVisitedDirectory(); });
    expander->registerVariable("HostOs:isWindows",
                               tr("Is %1 running on Windows?").arg(Constants::IDE_DISPLAY_NAME),
                               []() { return QVariant(Utils::HostOsInfo::isWindowsHost()).toString(); });
    expander->registerVariable("HostOs:isOSX",
                               tr("Is %1 running on OS X?").arg(Constants::IDE_DISPLAY_NAME),
                               []() { return QVariant(Utils::HostOsInfo::isMacHost()).toString(); });
    expander->registerVariable("HostOs:isLinux",
                               tr("Is %1 running on Linux?").arg(Constants::IDE_DISPLAY_NAME),
                               []() { return QVariant(Utils::HostOsInfo::isLinuxHost()).toString(); });
    expander->registerVariable("HostOs:isUnix",
                               tr("Is %1 running on any unix-based platform?")
                                   .arg(Constants::IDE_DISPLAY_NAME),
                               []() { return QVariant(Utils::HostOsInfo::isAnyUnixHost()).toString(); });
    expander->registerVariable("IDE:ResourcePath",
                               tr("The directory where %1 finds its pre-installed resources.")
                                   .arg(Constants::IDE_DISPLAY_NAME),
                               []() { return ICore::resourcePath(); });
    expander->registerPrefix("CurrentDate:", tr("The current date (QDate formatstring)."),
                             [](const QString &fmt) { return QDate::currentDate().toString(fmt); });
    expander->registerPrefix("CurrentTime:", tr("The current time (QTime formatstring)."),
                             [](const QString &fmt) { return QTime::currentTime().toString(fmt); });
    expander->registerVariable("UUID", tr("Generate a new UUID."),
                               []() { return QUuid::createUuid().toString(); });

    expander->registerPrefix("#:", tr("A comment."), [](const QString &) { return QString(); });

    // Make sure all wizards are there when the user might access the keyboard shortcuts:
    connect(ICore::instance(), &ICore::optionsDialogRequested, []() { IWizardFactory::allWizardFactories(); });

    Utils::PathChooser::setAboutToShowContextMenuHandler(&CorePlugin::addToPathChooserContextMenu);*/

    return success;
}

void CorePlugin::extensionsInitialized()
{
    m_mainWindow->extensionsInitialized();
    /* if (m_designMode->designModeIsRequired())
        addObject(m_designMode);
    Find::extensionsInitialized();
    m_locator->extensionsInitialized();
    m_mainWindow->extensionsInitialized();
    if (ExtensionSystem::PluginManager::hasError()) {
        auto errorOverview = new ExtensionSystem::PluginErrorOverview(m_mainWindow);
        errorOverview->setAttribute(Qt::WA_DeleteOnClose);
        errorOverview->setModal(true);
        errorOverview->show();
    } */
}

bool CorePlugin::delayedInitialize()
{
    // HelpManager::setupHelpManager();
    // m_locator->delayedInitialize();
    // IWizardFactory::allWizardFactories(); // scan for all wizard factories
    return true;
}
