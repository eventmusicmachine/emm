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

#ifndef IDRIVER_H
#define IDRIVER_H

#include <QObject>

#include "audio_global.h"

namespace Audio {

class IDevice;

class AUDIO_EXPORT IDriver : public QObject
{
    Q_OBJECT
public:
    virtual ~IDriver();
    QList<IDevice*> devices() const;

    virtual QString id() const = 0;
    virtual QString name() const = 0;
    virtual QStringList supportedMimeTypes() const = 0;

protected:
    QList<IDevice*> m_devices;
};

} // namespace Audio

#endif // IDRIVER_H
