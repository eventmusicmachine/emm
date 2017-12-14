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

#include <QApplication>

#include "icore.h"
#include "mainwindow.h"

using namespace Core;
using namespace Core::Internal;

static ICore *m_instance = nullptr;
static MainWindow *m_mainwindow = nullptr;

ICore::ICore(MainWindow *mainwindow)
{
    m_instance = this;
    m_mainwindow = mainwindow;
}

ICore::~ICore()
{
    m_instance = 0;
    m_mainwindow = 0;
}

ICore *ICore::instance()
{
    return m_instance;
}

QWidget *ICore::dialogParent()
{
    QWidget *active = QApplication::activeModalWidget();
    if (!active)
        active = QApplication::activeWindow();
    if (!active)
        active = m_mainwindow;
    return active;
}
