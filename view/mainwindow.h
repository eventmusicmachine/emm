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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>

namespace Ui {
    class MainWindow;
}
class PlayerWidget;
class QFileSystemModel;
class LoadSlotThread;
class QNetworkReply;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
protected:
    void wheelEvent(QWheelEvent *);

private:
    Ui::MainWindow *ui;
    QList<PlayerWidget*> playerWidgets;
    QFileSystemModel *fileModel;
    LoadSlotThread *slotThread;
    bool pauseModifier;

private slots:
    void showConfigDialog();
    void showErrorMessage(QString);
    void showBassErrorMessage(int code);
    void createPlayers();
    void updateSlotAssignment();
    void keyboardSignal(int key, int pressed);
    void setAutoPlay();
    void showAbout();
    void showSlotStore();
    void copyColors();
    void clearSlots();
    void setConfigDirectory();

};

#endif // MAINWINDOW_H
