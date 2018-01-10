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

    QMap<QString, IDriver*> drivers = DeviceManager::instance()->drivers();
    foreach (QString key, drivers.keys())
    {
        IDriver *driver = drivers.value(key);
        m_ui->driverComboBox->addItem(driver->name(), driver->id());
    }

    m_channel = 1;
}

OutputSelectionWidget::~OutputSelectionWidget()
{
    delete m_ui;
}

QString OutputSelectionWidget::driver() const
{
    return m_ui->driverComboBox->currentData().toString();
}

int OutputSelectionWidget::device() const
{
    return m_ui->deviceComboBox->currentData().toInt();
}

int OutputSelectionWidget::channel() const
{
    return m_ui->channelSpinBox->value();
}

void OutputSelectionWidget::setSelection(QString driver, int device, int channel)
{
    int driverIndex = m_ui->driverComboBox->findData(driver);
    m_driver = driver;
    m_ui->driverComboBox->setCurrentIndex(driverIndex);

    m_device = m_ui->deviceComboBox->findData(device);
    m_ui->deviceComboBox->setCurrentIndex(m_device);

    m_channel = channel;
    m_ui->channelSpinBox->setValue(channel);
}

void OutputSelectionWidget::driverChanged(int index)
{
    m_ui->deviceComboBox->clear();
    QMap<QString, IDriver*> drivers = DeviceManager::instance()->drivers();
    m_driver = m_ui->driverComboBox->itemData(index).toString();
    QList<IDevice*> devices = drivers.value(m_driver)->devices();

    for (int i = 0; i < devices.length(); i++)
    {
        IDevice *device = devices.at(i);
        m_ui->deviceComboBox->addItem(device->name(), i);
    }
}

void OutputSelectionWidget::deviceChanged(int index)
{
    if (index < 0) return;

    if (m_deviceInstance) {
        disconnect(m_deviceInstance, &IDevice::outputCountUpdated, this, &OutputSelectionWidget::outputCountChanged);
    }

    QMap<QString, IDriver*> drivers = DeviceManager::instance()->drivers();
    m_deviceInstance = drivers.value(m_driver)->devices().at(index);
    connect(m_deviceInstance, &IDevice::outputCountUpdated, this, &OutputSelectionWidget::outputCountChanged);
    int outputCount = m_deviceInstance->outputCount();
    outputCountChanged(outputCount);
}

void OutputSelectionWidget::outputCountChanged(int count)
{
    if (count > 0) {
        m_ui->channelSpinBox->setMinimum(1);
        m_ui->channelSpinBox->setMaximum(count);
        m_ui->channelSpinBox->setValue(m_channel);
    } else {
        m_ui->channelSpinBox->setMinimum(0);
        m_ui->channelSpinBox->setMaximum(0);
        m_ui->channelSpinBox->setValue(0);
    }
}
