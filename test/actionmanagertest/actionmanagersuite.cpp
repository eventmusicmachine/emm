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

#include <QAction>
#include <actionmanager/action.h>
#include <actionmanager/actionmanager.h>

#include "actionmanagersuite.h"
#include "testtrigger.h"

using namespace Actions;

void ActionManagerSuite::initTestCase()
{
    ActionManager::initialize(this);
}

void ActionManagerSuite::testInit()
{
    ActionManager *am = ActionManager::instance();

    QVERIFY2(am != 0, "Instance was not created");
}

void ActionManagerSuite::testRegisterAction()
{
    QAction *action = new QAction();
    ActionManager *am = ActionManager::instance();

    Action *internalAction = am->registerAction(action, "TEST");

    QCOMPARE(internalAction->id(), "TEST");
    QCOMPARE(internalAction->action(), action);
}

void ActionManagerSuite::testRegisterTrigger()
{
    TestTrigger *trigger = new TestTrigger();
    // ActionManager *am = ActionManager::instance();

    // Trigger *triggerInstance = am->registerTrigger(trigger, "TEST");
}
