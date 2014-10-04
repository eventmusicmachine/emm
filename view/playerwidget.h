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

#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>

namespace Ui {
    class PlayerWidget;
}

class PlaylistPlayer;
class PlaylistEntry;

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(int number, QWidget *parent = 0);
    ~PlayerWidget();
    int getNumber();

private:
    Ui::PlayerWidget *ui;
    double length;
    int number;
    PlaylistPlayer *player;
    void showInfo();

private slots:
    void editPlayer();
    void updateLength(double length);
    void updatePosition(double pos);
    void entryLoaded(PlaylistEntry* entry);
    void history(PlaylistEntry*);

signals:
    void addToHistory(PlaylistEntry*);

};

#endif // PLAYERWIDGET_H
