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

#ifndef ICORE_H
#define ICORE_H

#include <QObject>

#include "core_global.h"

namespace Core {

namespace Internal {

class MainWindow;

} // namespace Internal

class CORE_EXPORT ICore : public QObject
{
    Q_OBJECT
public:
    static ICore *instance();

    static QWidget *dialogParent();

private:
    explicit ICore(Internal::MainWindow *mw);
    ~ICore();

    friend class Internal::MainWindow;
};

} // namespace Core



#endif // ICORE_H
