﻿/* ***************************************************************************
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

#ifndef PLAYLISTENTRY_H
#define PLAYLISTENTRY_H

#include <QObject>

class QTimer;

class PlaylistEntry : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistEntry(QString filename, QObject *parent = 0);
    QString getArtist();
    QString getTitle();
    QString getFilename();
    double getLength();
private:

    QString artist;
    QString title;
    double length;
    QString filename;
};

#endif // PLAYLISTENTRY_H
