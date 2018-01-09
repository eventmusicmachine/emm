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

#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>

#include "audio_global.h"

namespace Audio {

class IDriver;

namespace Internal {

class AudioPlugin;

} // namespace Internal

class AUDIO_EXPORT DeviceManager : public QObject
{
    Q_OBJECT
public:
    void registerDriver(IDriver* device);
    QMap<QString, IDriver*> drivers();
    static DeviceManager *instance();

private:
    DeviceManager(QObject *parent = nullptr);
    ~DeviceManager();

    friend class Internal::AudioPlugin;
};

} // namespace Audio

#endif // DEVICEMANAGER_H
