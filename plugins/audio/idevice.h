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

#ifndef IDEVICE_H
#define IDEVICE_H

#include <QObject>
#include "audio_global.h"

namespace Audio {

class AUDIO_EXPORT IDevice : public QObject
{
  Q_OBJECT
public:
    virtual QString name() = 0;
    virtual int channelCount() = 0;

signals:
    void channelCountUpdated(int count);

};

} // namespace Audio

#endif // IDEVICE_H
