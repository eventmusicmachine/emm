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


#ifndef SIGNAL_H
#define SIGNAL_H

#include <QObject>
#include <QEvent>

#include "actionmanager_global.h"

namespace Actions {

namespace Internal {

class SignalPrivate;

} // namespace Internal

class ACTIONMANAGER_EXPORT Signal : public QObject
{
    Q_OBJECT
public:
    Signal(QString id, QString descripton, QObject *parent = 0);

protected:
    Signal(Internal::SignalPrivate &d);
    Internal::SignalPrivate *d;

};

} // namespace Actions

#endif // SIGNAL_H
