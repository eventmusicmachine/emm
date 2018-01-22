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

using namespace Actions;
using namespace Actions::Internal;

MouseSignal::MouseSignal() : Signal(*new MouseSignalPrivate) {

}

MouseSignal::MouseSignal(Qt::MouseButtons buttons) : Signal(*new MouseSignalPrivate(buttons)) {

}

void MouseSignal::send(QMouseEvent *event)
{
    MouseSignalPrivate *d2 = static_cast<MouseSignalPrivate *>(d);

    if (d2->m_buttons == event->buttons()) {
        emit triggered();
    }
}

MouseSignalPrivate::MouseSignalPrivate() : SignalPrivate()
{
}

MouseSignalPrivate::MouseSignalPrivate(Qt::MouseButtons buttons) :
    SignalPrivate(),
    m_buttons(buttons)
{
}
