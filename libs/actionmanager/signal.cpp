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


#include "signal.h"
#include "signal_p.h"

using namespace Actions;
using namespace Actions::Internal;


Signal::Signal(QString id, QString description, QObject *parent) : QObject(parent),
    d(new SignalPrivate(this))
{
    d->m_id = id;
    d->m_description = description;
}

Signal::Signal(SignalPrivate &d_ptr) : d(&d_ptr)
{
}

SignalPrivate::SignalPrivate(QObject *parent) : QObject(parent)
{

}
