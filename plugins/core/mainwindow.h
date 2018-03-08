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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "icore.h"

QT_BEGIN_NAMESPACE
class QToolBar;
class QButtonGroup;
class QStackedWidget;
QT_END_NAMESPACE

namespace ExtensionSystem {
    class PluginErrorOverview;
}

namespace Core {

namespace Internal {

class AboutDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool init(QString *errorMessage);
    void extensionsInitialized();

private:
    void about();
    void destroyAboutDialog();
    void plugins();
    void destroyPluginsDialog();
    void actionManager();

    ICore *m_coreImpl = nullptr;
    AboutDialog *m_aboutDialog = nullptr;
    ExtensionSystem::PluginErrorOverview *m_pluginOverview = nullptr;
    QToolBar *m_toolBar = nullptr;
    QButtonGroup *m_toolBarButtons = nullptr;
    QStackedWidget *m_componentStack = nullptr;
};

} // namespace Internal
} // namespace Core

#endif // MAINWINDOW_H
