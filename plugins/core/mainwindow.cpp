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
#include <QMenuBar>
#include <actionmanager/actionmanager.h>
#include <actionmanager/actioncontainer.h>
#include <extensionsystem/pluginerroroverview.h>

#include "mainwindow.h"
#include "aboutdialog.h"

using namespace Core;
using namespace Core::Internal;
using namespace Actions;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_coreImpl(new ICore(this))
{
    setWindowTitle("Event Music Machine");

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
}

MainWindow::~MainWindow()
{

}

bool MainWindow::init(QString *errorMessage)
{
    Q_UNUSED(errorMessage)

    return true;
}

void MainWindow::extensionsInitialized()
{
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
