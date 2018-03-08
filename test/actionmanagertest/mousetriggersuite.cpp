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

#include <QSignalSpy>
#include <actionmanager/actionmanager.h>
#include <actionmanager/mousetrigger.h>
#include <actionmanager/receiver.h>

#include "mousetriggersuite.h"
#include "mousesignalwidget.h"

using namespace Actions;

void MouseTriggerSuite::testLeftClick()
{
    MouseTrigger *trigger = new MouseTrigger(this);
    MouseSignal *signal = static_cast<MouseSignal *>(trigger->createSignal("ID", "Click Widget"));
    MouseSignalWidget *widget = new MouseSignalWidget(signal);
    QSignalSpy spy(signal, &MouseSignal::triggered);

    QTest::mousePress(widget, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);

    delete widget;
}

void MouseTriggerSuite::testConnection()
{
    ActionManager::initialize(this);
    ActionManager *actionManager = ActionManager::instance();

    MouseTrigger *trigger = new MouseTrigger(this);
    MouseSignal *signal = static_cast<MouseSignal *>(trigger->createSignal("TEST_SIGNAL", "Click Widget"));
    MouseSignalWidget *widget = new MouseSignalWidget(signal);

    Receiver *receiver = new Receiver;
    actionManager->registerReceiver("TEST_REICEIVER", receiver);

    signal->connect(receiver, Qt::LeftButton);

    // QSignalSpy spy(receiver, &Receiver::received);

    // QTest::mousePress(widget, Qt::LeftButton);

    // QCOMPARE(spy.count(), 1);

    delete widget;
}
