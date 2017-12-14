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

#ifndef ACTIONCONTAINER_P_H
#define ACTIONCONTAINER_P_H

#include <QPointer>

#include "actioncontainer.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QMenuBar;
QT_END_NAMESPACE

namespace Actions {

namespace Internal {

class ActionContainerPrivate : public ActionContainer
{
  Q_OBJECT

public:
    ActionContainerPrivate(QString id);
    ~ActionContainerPrivate() {}

    void addAction(Action *action);
    void addMenu(ActionContainer *menu);

    QMenu *menu() const;
    QMenuBar *menuBar() const;

    virtual void addAction(QAction *action) = 0;
    virtual void addMenu(QMenu *menu) = 0;

protected:
    virtual bool canBeAddedToMenu() const = 0;

private:
    QString m_id;
};

class MenuActionContainer : public ActionContainerPrivate
{
public:
    explicit MenuActionContainer(QString id);
    ~MenuActionContainer();

    QMenu *menu() const;

    void addAction(QAction *action);
    void addMenu(QMenu *menu);

protected:
    bool canBeAddedToMenu() const;

private:
    QPointer<QMenu> m_menu;
};

class MenuBarActionContainer : public ActionContainerPrivate
{
public:
    explicit MenuBarActionContainer(QString id);
    ~MenuBarActionContainer();

    QMenuBar *menuBar() const;

    void addAction(QAction *action);
    void addMenu(QMenu *menu);

protected:
    bool canBeAddedToMenu() const;

private:
    QPointer<QMenuBar> m_menuBar;
};

} // namespace Internal
} // namespace Actions

#endif // ACTIONCONTAINER_P_H
