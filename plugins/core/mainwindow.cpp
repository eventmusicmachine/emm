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
#include <QButtonGroup>
#include <QMenuBar>
#include <QStackedWidget>
#include <QToolBar>
#include <QToolButton>

#include <actionmanager/actionmanager.h>
#include <actionmanager/actioncontainer.h>
#include <extensionsystem/pluginerroroverview.h>
#include <extensionsystem/pluginmanager.h>

#include "mainwindow.h"
#include "aboutdialog.h"
#include "icentralcomponentfactory.h"

using namespace Core;
using namespace Core::Internal;
using namespace Actions;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_coreImpl(new ICore(this)),
    m_toolBar(new QToolBar(this)),
    m_toolBarButtons(new QButtonGroup(this)),
    m_componentStack(new QStackedWidget(this))
{
    setWindowTitle("Event Music Machine");
    setCentralWidget(m_componentStack);
    addToolBar(Qt::LeftToolBarArea, m_toolBar);

    ActionContainer *menuBar = ActionManager::createMenuBar("MAIN_MENU");
    setMenuBar(menuBar->menuBar());

    ActionContainer *fileMenu = ActionManager::createMenu("FILE_MENU");
    fileMenu->menu()->setTitle(tr("File"));
    menuBar->addMenu(fileMenu);

    ActionContainer *helpMenu = ActionManager::createMenu("HELP_MENU");
    helpMenu->menu()->setTitle(tr("Help"));
    menuBar->addMenu(helpMenu);

    // Exit Action
    QAction *exitAction = new QAction(tr("E&xit"), this);
    exitAction->setMenuRole(QAction::QuitRole);
    Action *e = ActionManager::registerAction(exitAction, "EXIT");
    fileMenu->addAction(e);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    // About Action
    QAction *aboutAction = new QAction(tr("About..."), this);
    aboutAction->setMenuRole(QAction::AboutRole);
    Action *e2 = ActionManager::registerAction(aboutAction, "ABOUT");
    helpMenu->addAction(e2);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    // About Action
    QAction *pluginsAction = new QAction(tr("Plugins..."), this);
    Action *e3 = ActionManager::registerAction(pluginsAction, "PLUGINS");
    helpMenu->addAction(e3);
    connect(pluginsAction, &QAction::triggered, this, &MainWindow::plugins);

    connect(m_toolBarButtons, SIGNAL(buttonPressed(int)), m_componentStack, SLOT(setCurrentIndex(int)));
}

MainWindow::~MainWindow()
{
    delete m_coreImpl;
    m_coreImpl = nullptr;

    delete m_toolBarButtons;
    m_toolBarButtons = nullptr;

    delete m_toolBar;
    m_toolBar = nullptr;

    delete m_componentStack;
    m_componentStack = nullptr;
}

bool MainWindow::init(QString *errorMessage)
{
    Q_UNUSED(errorMessage)

    return true;
}

void MainWindow::extensionsInitialized()
{
    // Create central components
    QList<ICentralComponentFactory*> components = ExtensionSystem::PluginManager::getObjects<ICentralComponentFactory>();
    foreach (ICentralComponentFactory *component, components) {
        QToolButton *button = new QToolButton(this);
        button->setText(component->displayName());
        button->setCheckable(true);
        m_toolBar->addWidget(button);
        m_toolBarButtons->addButton(button);
        m_componentStack->addWidget(component->createComponent(this));
    }

    // Automatically activate first button
    if (m_toolBarButtons->buttons().length() > 0) {
        m_toolBarButtons->buttons().first()->setChecked(true);
    }

    showMaximized();
}

void MainWindow::about()
{
    if (!m_aboutDialog) {
        m_aboutDialog = new AboutDialog(this);
        connect(m_aboutDialog, &QDialog::finished, this, &MainWindow::destroyAboutDialog);
        m_aboutDialog->show();
    }
}

void MainWindow::destroyAboutDialog()
{
    if (m_aboutDialog) {
        m_aboutDialog->deleteLater();
        m_aboutDialog = 0;
    }
}

void MainWindow::plugins()
{
    if (!m_pluginOverview) {
        m_pluginOverview = new ExtensionSystem::PluginErrorOverview(this);
        connect(m_pluginOverview, &QDialog::finished, this, &MainWindow::destroyPluginsDialog);
        m_pluginOverview->show();
    }
}

void MainWindow::destroyPluginsDialog()
{
    if (m_pluginOverview) {
        m_pluginOverview->deleteLater();
        m_pluginOverview = 0;
    }
}
