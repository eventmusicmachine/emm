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

#include "navigationtreeitem.h"
#include "navigationtreeitem_p.h"
#include "isettingspagefactory.h"

using namespace Settings;
using namespace Settings::Internal;

NavigationTreeItemPrivate::NavigationTreeItemPrivate(QString id, QString text, NavigationTreeItemPrivate *parent)
    : m_id(id),
      m_text(text),
      m_parentItem(parent)
{

}

NavigationTreeItemPrivate::~NavigationTreeItemPrivate()
{
    if (m_factory) {
        delete m_factory;
    }
}

void NavigationTreeItemPrivate::addChild(NavigationTreeItem *item)
{
    NavigationTreeItemPrivate *itemPrivate = static_cast<NavigationTreeItemPrivate *>(item);
    itemPrivate->m_parentItem = this;
    m_childItems.append(itemPrivate);
}

NavigationTreeItem *NavigationTreeItemPrivate::child(int row)
{
    return m_childItems.value(row);
}

int NavigationTreeItemPrivate::childCount() const
{
    return m_childItems.count();
}

int NavigationTreeItemPrivate::columnCount() const
{
    return 1;
}

QVariant NavigationTreeItemPrivate::data(int column) const
{
    Q_UNUSED(column)

    return m_text;
}

NavigationTreeItem *NavigationTreeItemPrivate::parentItem()
{
    return m_parentItem;
}

int NavigationTreeItemPrivate::row() const
{
    if (m_parentItem) {
        return m_parentItem->m_childItems.indexOf(const_cast<NavigationTreeItemPrivate*>(this));
    }

    return 0;
}

ISettingsPageFactory *NavigationTreeItemPrivate::factory() const
{
    return m_factory;
}

void NavigationTreeItemPrivate::setFactory(ISettingsPageFactory *factory)
{
    m_factory = factory;
}
