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

#ifndef BASSDEVICE_H
#define BASSDEVICE_H

#include "abstractbassdevice.h"

class BassDevice : public AbstractBassDevice
{
    Q_OBJECT
public:
    static void initialize(MainWindow *mw);
    static QList<BassDevice*> getAllDevices();
    static BassDevice* getDeviceWithID(int id);
    static void setBuffer(int ms);
    static DWORD getSpeakerFlag(int channel);
    void init();
    bool setOutputDevice();

private:
    BASS_DEVICEINFO deviceInfo;
    static DWORD CALLBACK proc(HSTREAM handle, void *buf, DWORD len, void *user);

    void free();

};

#endif // BASSDEVICE_H
