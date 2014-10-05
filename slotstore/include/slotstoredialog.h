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

#ifndef SLOTSTOREDIALOG_H
#define SLOTSTOREDIALOG_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
    class SlotStoreDialog;
}

class SlotTableModel;
class QSortFilterProxyModel;

class SlotStoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SlotStoreDialog(QWidget *parent = 0);
    ~SlotStoreDialog();

private:
    Ui::SlotStoreDialog *ui;
    SlotTableModel *model;
    QSortFilterProxyModel *sortModel;

private slots:
    void addSlot();
    void editSlot();
    void editSlot(QModelIndex);
    void removeSlot();
};

#endif // SLOTSTOREDIALOG_H
