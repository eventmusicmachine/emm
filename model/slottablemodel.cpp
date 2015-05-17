/* ***************************************************************************
 * This file is part of Event Music Machine.
 *
 * Event Music Machine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Event Music Machine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Event Music Machine. If not, see <http://www.gnu.org/licenses/>.
 * ************************************************************************* */

#include <QColor>
#include <QMimeData>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "model/audio/cartslot.h"
#include "slottablemodel.h"

SlotTableModel::SlotTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int SlotTableModel::rowCount(const QModelIndex &parent) const
{
    return slot.size();
}

int SlotTableModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QVariant SlotTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        CartSlot* s = slot.at(row);
        switch (index.column())
        {
        case 0: return s->getNumber();
        case 1: return s->getText1();
        case 2: return s->getFileName();
        case 3: return s->getColor();
        case 4: return s->getFontColor();
        case 5: {
            int usedId = CartSlot::isUsed(s->getFileName());
            if (usedId == -1) {
                return "X";
            }
            return usedId;
        }
        }
    }
    else if (role == Qt::BackgroundRole || role == Qt::ForegroundRole)
    {
        if (index.column() > 2)
        {
            CartSlot* s = slot.at(index.row());
            switch (index.column())
            {
            case 3: return QColor(s->getColor());
            case 4: return QColor(s->getFontColor());
            }
        }

    }
    return QVariant();
}

QVariant SlotTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0: return "ID";
        case 1: return "Name";
        case 2: return "Datei";
        // m2: changed labels
        case 3: return "HF";
        case 4: return "SF";
        //case 3: return "Farbe";
        //case 4: return "Textfarbe";
        case 5: return "SlotID";
        }
    }
    return QVariant();
}

Qt::ItemFlags SlotTableModel::flags(const QModelIndex &) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
}

QMimeData* SlotTableModel::mimeData(const QModelIndexList &indexes) const
{
    if (indexes.size() == 0)
        return 0;

    QMimeData *mimeData = new QMimeData();
    int id = data(index(indexes.at(0).row(),0),Qt::DisplayRole).toInt();
    QByteArray encodedData = QByteArray::number(id);
    mimeData->setData("application/emm.store.objectid",encodedData);
    return mimeData;
}

Qt::DropActions SlotTableModel::supportedDragActions() const
{
    return Qt::CopyAction;
}

void SlotTableModel::loadData()
{
    this->beginResetModel();
    QSqlQuery query("SELECT slot_id FROM slots");
    QList<CartSlot*> slotList;
    while (query.next())
    {
        CartSlot* s = CartSlot::getObjectWithNumber(query.value(0).toInt(),true);
        slotList.append(s);
    }
    slot = slotList;

    this->endResetModel();
}

void SlotTableModel::removeWithId(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM slots WHERE slot_id=?");
    query.bindValue(0,id);
    query.exec();
}
