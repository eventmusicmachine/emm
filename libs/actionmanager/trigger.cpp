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

#include "trigger.h"
#include "trigger_p.h"
#include "signal.h"

using namespace Actions;
using namespace Actions::Internal;

Trigger::Trigger(QObject *parent) : QObject(parent),
    d(new TriggerPrivate(this))
{
}

Trigger::Trigger(TriggerPrivate &d_ptr) : d(&d_ptr)
{
}

Signal* Trigger::signal(QString id) const
{
    return d->m_signals.value(id);
}

TriggerPrivate::TriggerPrivate(QObject *parent) : QObject(parent)
{

}

TriggerPrivate::~TriggerPrivate()
{
    qDeleteAll(m_signals);
}
