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

#ifndef ACTIONCONTAINER_H
#define ACTIONCONTAINER_H

#include <QObject>

#include "actionmanager_global.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QMenuBar;
class QAction;
QT_END_NAMESPACE

namespace Actions {

class Action;

class ACTIONMANAGER_EXPORT ActionContainer : public QObject
{
    Q_OBJECT
public:
    virtual QMenu *menu() const = 0;
    virtual QMenuBar *menuBar() const = 0;

    virtual void addAction(Action *action) = 0;
    virtual void addMenu(ActionContainer *menu) = 0;
};

} // namespace Actions


#endif // ACTIONCONTAINER_H
