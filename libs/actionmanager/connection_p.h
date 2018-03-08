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

#ifndef CONNECTION_P_H
#define CONNECTION_P_H

#include <QObject>
#include <QSharedPointer>

namespace Actions {

class Signal;
class Receiver;

namespace Internal {

class ConnectionPrivate : public QObject
{
    Q_OBJECT
public:
    ConnectionPrivate(QObject *parent = 0);

    QSharedPointer<Signal> m_signal;
    QSharedPointer<Receiver> m_receiver;
};

} // namespace Internal
} // namespace Actions

#endif // CONNECTION_P_H
