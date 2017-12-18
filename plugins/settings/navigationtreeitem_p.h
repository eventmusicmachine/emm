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

#ifndef NAVIGATIONTREEITEM_P_H
#define NAVIGATIONTREEITEM_P_H

#include <QList>

#include "navigationtreeitem.h"

namespace Settings {

class NavigationTreeItem;

namespace Internal {

class NavigationTreeItemPrivate : public NavigationTreeItem {

public:
    NavigationTreeItemPrivate(QString id, QString text, NavigationTreeItemPrivate *parent = 0);
    ~NavigationTreeItemPrivate();

    void addChild(NavigationTreeItem *child);

    NavigationTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    NavigationTreeItem *parentItem();

private:
    QString m_id;
    QString m_text;
    QList<NavigationTreeItemPrivate*> m_childItems;
    NavigationTreeItemPrivate *m_parentItem;

};

} // namespace Internal
} // namespace Settings

#endif // NAVIGATIONTREEITEM_P_H
