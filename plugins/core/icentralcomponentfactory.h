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

#ifndef ICENTRALCOMPONENTFACTORY_H
#define ICENTRALCOMPONENTFACTORY_H

#include <QObject>

#include "core_global.h"

class CORE_EXPORT ICentralComponentFactory : public QObject
{
    Q_OBJECT
public:
    virtual QString displayName() const = 0;
    virtual QWidget *createComponent(QWidget *parent) = 0;
};

#endif // ICENTRALCOMPONENTFACTORY_H
