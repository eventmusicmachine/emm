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

#include "mousesignal.h"
#include "mousesignal_p.h"
#include "mouseconnection.h"

using namespace Actions;
using namespace Actions::Internal;

MouseSignal::MouseSignal(QString id, QString description) : Signal(*new MouseSignalPrivate) {
    d->m_id = id;
    d->m_description = description;
}

void MouseSignal::send(QMouseEvent *event)
{
    emit triggered(event->buttons());
}

void MouseSignal::connect(Receiver *receiver, Qt::MouseButtons buttons)
{
    MouseSignalPrivate *d_ptr = static_cast<MouseSignalPrivate*>(d);
    d_ptr->m_connections.append(new MouseConnection(this, receiver, buttons));
}

MouseSignalPrivate::~MouseSignalPrivate()
{
    qDeleteAll(m_connections);
}
