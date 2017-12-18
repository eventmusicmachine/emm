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

#ifndef NAVIGATIONTREEITEM_H
#define NAVIGATIONTREEITEM_H

#include <QVariant>

#include "settings_global.h"

namespace Settings {

class SETTINGS_EXPORT NavigationTreeItem
{
public:
    virtual void addChild(NavigationTreeItem *child) = 0;

    virtual NavigationTreeItem *child(int row) = 0;
    virtual int childCount() const = 0;
    virtual int columnCount() const = 0;
    virtual QVariant data(int column) const = 0;
    virtual int row() const = 0;
    virtual NavigationTreeItem *parentItem() = 0;

};

} // namespace Settings

#endif // NAVIGATIONTREEITEM_H
