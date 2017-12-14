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

#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>

#include "actionmanager_global.h"

QT_BEGIN_NAMESPACE
class QAction;
class QString;
QT_END_NAMESPACE

namespace Actions {

class ActionContainer;
class Action;

class ACTIONMANAGERSHARED_EXPORT ActionManager : public QObject
{
    Q_OBJECT
public:
    static void initialize(QObject *parent);
    static ActionManager *instance();

    static ActionContainer *createMenu(QString id);
    static ActionContainer *createMenuBar(QString id);

    static Action *registerAction(QAction *action, QString id);

    static ActionContainer *actionContainer(QString id);

private:
    ActionManager(QObject *parent = 0);
    ~ActionManager();
};

} // namespace Actions

#endif // ACTIONMANAGER_H
