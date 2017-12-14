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

#include <QMenu>
#include <QMenuBar>

#include "actioncontainer.h"
#include "actioncontainer_p.h"
#include "action_p.h"

using namespace Actions;
using namespace Actions::Internal;

ActionContainerPrivate::ActionContainerPrivate(QString id) : m_id(id)
{

}

void ActionContainerPrivate::addAction(Action *action)
{
    addAction(action->action());
}

void ActionContainerPrivate::addMenu(ActionContainer *menu)
{
    ActionContainerPrivate *containerPrivate = static_cast<ActionContainerPrivate *>(menu);
    if (!containerPrivate->canBeAddedToMenu())
        return;

    MenuActionContainer *container = static_cast<MenuActionContainer *>(containerPrivate);
    addMenu(container->menu());
}

QMenu *ActionContainerPrivate::menu() const
{
    return 0;
}

QMenuBar *ActionContainerPrivate::menuBar() const
{
    return 0;
}

MenuActionContainer::MenuActionContainer(QString id)
    : ActionContainerPrivate(id), m_menu(new QMenu)
{
    m_menu->setObjectName(id);
}

MenuActionContainer::~MenuActionContainer()
{
    delete m_menu;
}

QMenu *MenuActionContainer::menu() const
{
    return m_menu;
}

void MenuActionContainer::addAction(QAction *action)
{
    m_menu->addAction(action);
}

void MenuActionContainer::addMenu(QMenu *menu)
{
    m_menu->addMenu(menu);
}

bool MenuActionContainer::canBeAddedToMenu() const
{
    return true;
}


MenuBarActionContainer::MenuBarActionContainer(QString id)
    : ActionContainerPrivate(id), m_menuBar(new QMenuBar)
{
    m_menuBar->setObjectName(id);
}

MenuBarActionContainer::~MenuBarActionContainer()
{
    delete m_menuBar;
}

QMenuBar *MenuBarActionContainer::menuBar() const
{
    return m_menuBar;
}


void MenuBarActionContainer::addAction(QAction *action)
{
    m_menuBar->addAction(action);
}

void MenuBarActionContainer::addMenu(QMenu *menu)
{
    m_menuBar->addMenu(menu);
}

bool MenuBarActionContainer::canBeAddedToMenu() const
{
    return false;
}
