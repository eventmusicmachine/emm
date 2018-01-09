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

#ifndef ABSTRACTBASSDEVICE_H
#define ABSTRACTBASSDEVICE_H

#include <QObject>
#include "bass.h"

class MainWindow;

class AbstractBassDevice : public QObject
{
    Q_OBJECT
public:
    explicit AbstractBassDevice(int deviceID, QObject *parent = 0);
    virtual QString getName()=0;
    int getDeviceID();
    int getChannelCount();
    void addStreamToMixer(HSTREAM stream,int channel,bool free=false);
    void unpause();
    static void setBuffer(int ms);

protected:
    int deviceID;

    virtual bool setOutputDevice()=0;
    virtual void init()=0;
    virtual void free()=0;

    void createChannels();

    int channelCount;
    QString name;
    QList<HSTREAM> streams;

signals:
    void errorOccured(int errorCode);

};

#endif // ABSTRACTBASSDEVICE_H
