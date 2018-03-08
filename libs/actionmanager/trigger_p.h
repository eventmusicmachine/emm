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

#ifndef TRIGGER_P_H
#define TRIGGER_P_H

#include <QObject>
#include <QMap>

namespace Actions {

class Signal;

namespace Internal {

class TriggerPrivate : public QObject
{
    Q_OBJECT
public:
    TriggerPrivate(QObject *parent = 0);
    ~TriggerPrivate();

    QMap<QString, Signal*> m_signals;
};


} // namespace Internal
} // namespace Actions

#endif // TRIGGER_P_H
