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

#include "connection.h"
#include "connection_p.h"
#include "signal.h"
#include "receiver.h"

using namespace Actions;
using namespace Actions::Internal;

Connection::Connection(Signal *signal, Receiver *receiver) :
    QObject(),
    d(new ConnectionPrivate(this))
{
    d->m_signal = QSharedPointer<Signal>(signal);
    d->m_receiver = QSharedPointer<Receiver>(receiver);
}

Connection::Connection(ConnectionPrivate &d_ptr) : d(&d_ptr)
{
}

ConnectionPrivate::ConnectionPrivate(QObject *parent) : QObject(parent)
{

}
