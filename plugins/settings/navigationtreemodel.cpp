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

#include "navigationtreemodel.h"
#include "navigationtreeitem.h"
#include "settingsmanager.h"

using namespace Settings;
using namespace Settings::Internal;

NavigationTreeModel::NavigationTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    // Get root item
    m_rootItem = SettingsManager::navigationNode("ROOT");
}

Qt::ItemFlags NavigationTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return 0;
    }

    return QAbstractItemModel::flags(index);
}

QVariant NavigationTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
            return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    NavigationTreeItem *item = static_cast<NavigationTreeItem*>(index.internalPointer());

    return item->data(index.column());
}

QModelIndex NavigationTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    NavigationTreeItem *parentItem;

    if (!parent.isValid()) {
        parentItem = m_rootItem;
    } else {
        parentItem = static_cast<NavigationTreeItem*>(parent.internalPointer());
    }

    NavigationTreeItem *childItem = parentItem->child(row);
    if (childItem) {
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex();
    }
}

QModelIndex NavigationTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }

    NavigationTreeItem *childItem = static_cast<NavigationTreeItem*>(index.internalPointer());
    NavigationTreeItem *parentItem = childItem->parentItem();

    if (parentItem == m_rootItem) {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int NavigationTreeModel::rowCount(const QModelIndex &parent) const
{
    NavigationTreeItem *parentItem;
    if (parent.column() > 0) {
        return 0;
    }
    if (!parent.isValid()) {
        parentItem = m_rootItem;
    } else {
        parentItem = static_cast<NavigationTreeItem*>(parent.internalPointer());
    }
    return parentItem->childCount();
}

int NavigationTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return static_cast<NavigationTreeItem*>(parent.internalPointer())->columnCount();
    } else {
        return m_rootItem->columnCount();
    }
}
