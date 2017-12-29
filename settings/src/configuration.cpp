﻿/* ***************************************************************************
 * This file is part of Event Music Machine.
 *
 * Event Music Machine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Event Music Machine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Event Music Machine. If not, see <http://www.gnu.org/licenses/>.
 * ************************************************************************* */

#include <QMutex>
#include <QSettings>
#include "configuration.h"
#include "bassdevice.h"

Configuration* Configuration::instance = 0;

int Configuration::getPFLDriver()
{
    return this->pflDriver;
}

int Configuration::getPFLDevice()
{
    return this->pflDevice;
}

int Configuration::getPFLChannel()
{
    return this->pflChannel;
}

int Configuration::getDefaultDriver()
{
    return this->defaultDriver;
}

int Configuration::getDefaultDevice()
{
    return this->defaultDevice;
}

int Configuration::getDefaultChannel()
{
    return this->defaultChannel;
}

int Configuration::getPlayer()
{
    return this->player;
}

int Configuration::getPlaylistFade()
{
    return this->playlistFade;
}

int Configuration::getSlotFade()
{
    return this->slotFade;
}

int Configuration::getPlaylistFPos()
{
    return this->playlistFPos;
}

int Configuration::getSlotBuffer()
{
    return this->slotBuffer;
}

bool Configuration::getLayerKeyboardSync()
{
    return this->layerKeyboardSync;
}

bool Configuration::getPauseButton()
{
    return this->pauseButton;
}

int Configuration::getSlotTimeSize() {
    return this->slotTimeSize;
}

void Configuration::setPFLDriver(int pflDriver)
{
    this->pflDriver = pflDriver;
}

void Configuration::setPFLDevice(int pflDevice)
{
    this->pflDevice = pflDevice;
}

void Configuration::setPFLChannel(int pflChannel)
{
    this->pflChannel = pflChannel;
}

void Configuration::setDefaultDriver(int defaultDriver)
{
    this->defaultDriver = defaultDriver;
}

void Configuration::setDefaultDevice(int defaultDevice)
{
    this->defaultDevice = defaultDevice;
}

void Configuration::setDefaultChannel(int defaultChannel)
{
    this->defaultChannel = defaultChannel;
}

void Configuration::setPlayer(int player)
{
    this->player = player;
}

void Configuration::setPlaylistFade(int playlistFade)
{
    this->playlistFade = playlistFade;
}

void Configuration::setSlotFade(int slotFade)
{
    this->slotFade = slotFade;
}

void Configuration::setPlaylistFPos(int playlistFPos)
{
    this->playlistFPos = playlistFPos;
}

void Configuration::setSlotBuffer(int slotBuffer)
{
    this->slotBuffer = slotBuffer;
}

void Configuration::setLayerKeyboardSync(bool layerKeyboardSync)
{
    this->layerKeyboardSync = layerKeyboardSync;
}

void Configuration::setPauseButton(bool pauseButton)
{
    this->pauseButton = pauseButton;
}

void Configuration::setSlotTimeSize(int size) {
    this->slotTimeSize = size;
}

void Configuration::readData()
{
    QSettings settings(Configuration::getStorageLocation() + "/config.ini", QSettings::IniFormat);
    pflDriver = settings.value("PFL/Type",0).toInt();
    pflDevice = settings.value("PFL/Device",1).toInt();
    pflChannel = settings.value("PFL/Channel",1).toInt();
    defaultDriver = settings.value("DefaultDevice/Type",0).toInt();
    defaultDevice = settings.value("DefaultDevice/Device",1).toInt();
    defaultChannel = settings.value("DefaultDevice/Channel",1).toInt();
    player = settings.value("Playlist/Player",2).toInt();
    playlistFade = settings.value("Playlist/Fade",4000).toInt();
    slotFade = settings.value("Slots/Fade",800).toInt();
    playlistFPos = settings.value("Playlist/FadePos",8000).toInt();
    slotBuffer = settings.value("Slots/Buffer",5000).toInt();
    layerKeyboardSync = settings.value("Slots/LayerKeyboardSync",false).toBool();
    pauseButton = settings.value("Slots/PauseButton",false).toBool();
    slotTimeSize = settings.value("Slots/TimeSize",10).toInt();
}

void Configuration::saveData()
{
    QSettings settings(Configuration::getStorageLocation() + "/config.ini", QSettings::IniFormat);
    settings.setValue("PFL/Type",pflDriver);
    settings.setValue("PFL/Device",pflDevice);
    settings.setValue("PFL/Channel",pflChannel);
    settings.setValue("DefaultDevice/Type",defaultDriver);
    settings.setValue("DefaultDevice/Device",defaultDevice);
    settings.setValue("DefaultDevice/Channel",defaultChannel);
    settings.setValue("Playlist/Player",player);
    settings.setValue("Playlist/Fade",playlistFade);
    settings.setValue("Slots/Fade",slotFade);
    settings.setValue("Playlist/FadePos",playlistFPos);
    settings.setValue("Slots/Buffer",slotBuffer);
    settings.setValue("Slots/LayerKeyboardSync",layerKeyboardSync);
    settings.setValue("Slots/TimeSize",slotTimeSize);
    settings.setValue("Slots/PauseButton",pauseButton);
    BassDevice::setBuffer(slotBuffer);
    // BassAsioDevice::setBuffer(slotBuffer);
}

Configuration* Configuration::getInstance()
{
    static QMutex mutex;
    if (!instance)
    {
        mutex.lock();

        if (!instance)
            instance = new Configuration;
        instance->readData();

        mutex.unlock();
    }
    return instance;
}

void Configuration::dropInstance()
{
    static QMutex mutex;
    mutex.lock();
    delete instance;
    instance = 0;
    mutex.unlock();
}

QString Configuration::getStorageLocation()
{
    QSettings settings("Christoph Krämer","EventMusicMachine");
    return settings.value("configPath","").toString();
}

void Configuration::setStorageLocation(QString location)
{
    QSettings settings("Christoph Krämer","EventMusicMachine");
    settings.setValue("configPath",location);
}
