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

#include "mousetrigger.h"
#include "mousesignal.h"
#include "action.h"

using namespace Actions;

MouseTrigger::MouseTrigger(QObject *parent) : Trigger(parent)
{
    qRegisterMetaType<Qt::MouseButtons>("MouseButtons");
}

Signal* MouseTrigger::createSignal(QString id, QString description)
{
    Signal *signal = new MouseSignal(id, description);
    return signal;
}
