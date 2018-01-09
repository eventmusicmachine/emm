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

#ifndef ABSTRACTAUDIOOBJECT_H
#define ABSTRACTAUDIOOBJECT_H

#include <QList>
#include <QMap>
#include <QObject>
#include "bass.h"

class QTimer;

class AbstractAudioObject : public QObject
{
    Q_OBJECT
public:
    bool isPlaying();
    bool isPaused();
    void fadeOut(int ms);
    bool isMissing();
    double getTimeLeft();
    void pause();
    virtual void loadStream(double vol=0);

protected:
    AbstractAudioObject(int , QObject * = 0);

    int number;
    bool playing;
    bool fading;
    bool paused;
    HSTREAM stream;
    QTimer *timer;
    QList<BASS_DX8_PARAMEQ> eqs;
	bool fileMissing;

    DWORD getSpeakerFlag();
    void unloadStream();
    void initDevice();
    static double DBToLevel(double db);

signals:
    void sendSongLength(double length);
    void sendCurrentPosition(double pos);
    void stopped();
    void started();

public slots:
    virtual void play();
    virtual void stop();

protected slots:
    virtual void readData()=0;
    virtual void saveData()=0;
    virtual void updatePosition();

};

#endif // ABSTRACTAUDIOOBJECT_H
