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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QItemSelection;
QT_END_NAMESPACE

namespace Settings {

class ISettingsPage;

namespace Internal {

class NavigationTreeModel;

namespace Ui {

class SettingsDialog;

} // namespace Ui

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private:
    Ui::SettingsDialog *m_ui;
    NavigationTreeModel *m_model;
    ISettingsPage *m_page = nullptr;

    QList<ISettingsPage*> m_visitedPages;

private slots:
    void showSettingsWidget(const QModelIndex &selected);
    void accept();
};

} // namespace Insternal
} // namespace Settings


#endif // SETTINGSDIALOG_H
