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

#include "outputselectionwidget.h"
#include "ui_outputselectionwidget.h"
#include "devicemanager.h"
#include "idriver.h"
#include "idevice.h"

using namespace Audio;

OutputSelectionWidget::OutputSelectionWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::OutputSelectionWidget)
{
    m_ui->setupUi(this);

    connect(m_ui->driverComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OutputSelectionWidget::driverChanged);
    connect(m_ui->deviceComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OutputSelectionWidget::deviceChanged);

    QList<IDriver*> drivers = DeviceManager::instance()->drivers();
    for (int i = 0; i < drivers.length(); i++)
    {
        IDriver *driver = drivers.at(i);
        m_ui->driverComboBox->addItem(driver->name(), i);
    }
}

OutputSelectionWidget::~OutputSelectionWidget()
{
    delete m_ui;
}

void OutputSelectionWidget::driverChanged(int index)
{
    m_ui->deviceComboBox->clear();
    QList<IDriver*> drivers = DeviceManager::instance()->drivers();
    m_selectedDriver = m_ui->driverComboBox->itemData(index).toInt();
    QList<IDevice*> devices = drivers.at(m_selectedDriver)->devices();
    //m_availableDevices = devices;
    for (int i = 0; i < devices.length(); i++)
    {
        IDevice *device = devices.at(i);
        m_ui->deviceComboBox->addItem(device->name(), i);
    }
}

void OutputSelectionWidget::deviceChanged(int index)
{
    QList<IDriver*> drivers = DeviceManager::instance()->drivers();
    int selectedDevice = m_ui->deviceComboBox->itemData(index).toInt();
    IDevice *device = drivers.at(m_selectedDriver)->devices().at(index);
    connect(device, &IDevice::channelCountUpdated, this, &OutputSelectionWidget::channelCountChanged);
    int channelCount = device->channelCount();
    channelCountChanged(channelCount);
}

void OutputSelectionWidget::channelCountChanged(int count)
{
    if (count > 0) {
        m_ui->channelSpinBox->setMinimum(1);
        m_ui->channelSpinBox->setMaximum(count);
        m_ui->channelSpinBox->setValue(1);
    } else {
        m_ui->channelSpinBox->setMinimum(0);
        m_ui->channelSpinBox->setMaximum(0);
        m_ui->channelSpinBox->setValue(0);
    }
}
