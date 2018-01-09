/* ***************************************************************************
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

#include <QSettings>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include "bass.h"
#include "bass_fx.h"
// #include "bassasiodevice.h"
#include "bassdevice.h"
#include "cartslot.h"
#include "configuration.h"
#include "playlistplayer.h"

QMap<int,CartSlot*> CartSlot::audioObjects = QMap<int,CartSlot*>();

CartSlot::CartSlot(int number, QObject *parent, bool db) :
    AbstractAudioObject(number, parent)
{
    this->number = number;
    this->database = db;
    readData();
    if (!db)
    {
        initDevice();
        audioObjects.insert(number,this);
        fetchLength();
    }
}

void CartSlot::fetchLength() {
    if (playing) return;
    this->loadStream();
    length = BASS_ChannelBytes2Seconds(stream,BASS_ChannelGetLength(stream,BASS_POS_BYTE));
    this->unloadStream();
    if (length < 0) length = 0;
    emit sendSongLength(length);
}

void CartSlot::play()
{
    if (this->isPlaying())
        this->cartStop();
    else
    {
        this->loadStream(db);
        if (this->loop)
            BASS_ChannelFlags(stream, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
        else
            BASS_ChannelFlags(stream, 0, BASS_SAMPLE_LOOP);
        BASS_ChannelSetAttribute(stream, BASS_ATTRIB_TEMPO, this->pitch);
        AbstractAudioObject::play();
        if (this->startPos>0)
            BASS_ChannelSetPosition(stream,BASS_ChannelSeconds2Bytes(stream,startPos),BASS_POS_BYTE);
        if (this->fadeOthers)
        {
            CartSlot::fadeOutAllSlots(this);
            PlaylistPlayer::fadeOutAllPlayers();
        }
        emit(startedPlaying());
    }
}

void CartSlot::cartStop()
{
    int fadeMs = Configuration::getInstance()->getSlotFade();
    if (this->fadeOutFlag)
        AbstractAudioObject::fadeOut(fadeMs);
    else
        AbstractAudioObject::stop();
}

bool CartSlot::getLetFade()
{
    return this->letFade;
}

bool CartSlot::getFadeOut()
{
    return this->fadeOutFlag;
}

bool CartSlot::getFadeOthers()
{
    return this->fadeOthers;
}

bool CartSlot::getLoop()
{
    return this->loop;
}

double CartSlot::getStartPos()
{
    return this->startPos;
}

double CartSlot::getStopPos()
{
    return this->stopPos;
}

int CartSlot::getPitch()
{
    return this->pitch;
}

double CartSlot::getDB()
{
    return this->db;
}

int CartSlot::getNumber()
{
    return this->number;
}

bool CartSlot::getEQActive()
{
    return this->eqActive;
}

QString CartSlot::getEQConfig()
{
    return this->eqConfig;
}

double CartSlot::getLength() {
    return this->length;
}

void CartSlot::setDataAndSave(QString filename, QString text1, int type, int device, int channel, QString color, QString fontColor, bool fadeOut, bool letFade, bool fadeOthers, bool loop, double startPos, double stopPos, int pitch, int fontSize, double db, bool eqActive, QString eqConfig)
{
    this->fadeOutFlag = fadeOut;
    this->fadeOthers = fadeOthers;
    this->letFade = letFade;
    this->loop = loop;
    this->startPos = startPos;
    this->stopPos = stopPos;
    this->pitch = pitch;
    this->db = db;
    this->eqActive = eqActive;
    this->eqConfig = eqConfig;
    this->saveData();
    if (!database)
    {
        this->initDevice();
        this->loadStream();
    }
}

void CartSlot::setColorsAndSave(QString color, QString fontColor)
{
    // this->color = color;
    // this->fontColor = fontColor;
    this->saveData();
}

void CartSlot::readData()
{
    if (!this->database || this->number == -1)
    {
        Configuration *config = Configuration::getInstance();
        QSettings settings(Configuration::getStorageLocation() + "/slots.ini", QSettings::IniFormat);
        letFade = settings.value("Slot"+QString::number(number)+"/LetFade",true).toBool();
        fadeOutFlag = settings.value("Slot"+QString::number(number)+"/FadeOut",true).toBool();
        fadeOthers = settings.value("Slot"+QString::number(number)+"/FadeOthers",true).toBool();
        loop = settings.value("Slot"+QString::number(number)+"/Loop",false).toBool();
        startPos = settings.value("Slot"+QString::number(number)+"/Start",0).toDouble();
        stopPos = settings.value("Slot"+QString::number(number)+"/Stop",0).toDouble();
        pitch = settings.value("Slot"+QString::number(number)+"/Pitch",0).toInt();
        db = settings.value("Slot"+QString::number(number)+"/DB",0).toDouble();
        eqActive = settings.value("Slot"+QString::number(number)+"/EqualizerActive",false).toBool();
        eqConfig = settings.value("Slot"+QString::number(number)+"/EqualizerConfig","").toString();
    }
    else
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM slots WHERE slot_id=?");
        query.bindValue(0,this->number);
        query.exec();
        query.next();
        // filename = query.value(1).toString();
        // text1 = query.value(2).toString();
        // color = query.value(3).toString();
        // fontColor = query.value(13).toString();
        letFade = query.value(6).toBool();
        fadeOutFlag = query.value(4).toBool();
        fadeOthers = query.value(5).toBool();
        loop = query.value(7).toBool();
        startPos = query.value(8).toDouble();
        stopPos = query.value(9).toDouble();
        pitch = query.value(10).toDouble();
        // fontSize = query.value(11).toInt();
        db = query.value(12).toDouble();
        eqActive = false;
        eqConfig = "";
    }
}

void CartSlot::saveData()
{
    if (!this->database)
    {
        QSettings settings(Configuration::getStorageLocation() + "/slots.ini", QSettings::IniFormat);
        settings.setValue("Slot"+QString::number(number)+"/LetFade",letFade);
        settings.setValue("Slot"+QString::number(number)+"/FadeOut",fadeOutFlag);
        settings.setValue("Slot"+QString::number(number)+"/FadeOthers",fadeOthers);
        settings.setValue("Slot"+QString::number(number)+"/Loop",loop);
        settings.setValue("Slot"+QString::number(number)+"/Start",startPos);
        settings.setValue("Slot"+QString::number(number)+"/Stop",stopPos);
        settings.setValue("Slot"+QString::number(number)+"/Pitch",pitch);
        settings.setValue("Slot"+QString::number(number)+"/DB",db);
        settings.setValue("Slot"+QString::number(number)+"/EqualizerActive",eqActive);
        settings.setValue("Slot"+QString::number(number)+"/EqualizerConfig",eqConfig);
    }
    else
    {
        QSqlQuery query;
        if (this->number == -1)
        {
            query.prepare("INSERT INTO slots (filename,desc,color,fade_out,fade_others,let_fade,loop,start_pos,stop_pos,pitch,font_size,db,font_color) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?)");
        }
        else
        {
            query.prepare("UPDATE slots SET filename=?,desc=?,color=?,fade_out=?,fade_others=?,let_fade=?,loop=?,start_pos=?,stop_pos=?,pitch=?,font_size=?,db=?,font_color=? WHERE slot_id=?");
            query.bindValue(13,number);
        }
        // query.bindValue(0,filename);
        // query.bindValue(1,text1);
        // query.bindValue(2,color);
        query.bindValue(3,fadeOutFlag);
        query.bindValue(4,fadeOthers);
        query.bindValue(5,letFade);
        query.bindValue(6,loop);
        query.bindValue(7,startPos);
        query.bindValue(8,stopPos);
        query.bindValue(9,pitch);
        // query.bindValue(10,fontSize);
        query.bindValue(11,db);
        // query.bindValue(12,fontColor);
        query.exec();
    }
}

CartSlot* CartSlot::getObjectWithNumber(int number, bool db)
{
    if (db)
    {
        return new CartSlot(number,0,db);
    }
    else
    {
        if (audioObjects.contains(number))
            return audioObjects.value(number);
        else
            return new CartSlot(number,0,db);
    }
}

void CartSlot::updatePosition()
{

    if (BASS_ChannelGetPosition(stream,BASS_POS_BYTE)>BASS_ChannelSeconds2Bytes(stream,BASS_ChannelBytes2Seconds(stream,BASS_ChannelGetLength(stream,BASS_POS_BYTE))-stopPos))
    {
        if (this->loop)
        {
            BASS_ChannelSetPosition(stream,BASS_ChannelSeconds2Bytes(stream,startPos),BASS_POS_BYTE);
        }
        else
        {
            stop();
        }
        return;
    }
    emit sendCurrentPosition(BASS_ChannelBytes2Seconds(stream,BASS_ChannelGetPosition(stream,BASS_POS_BYTE)));
    if (this->loop)
        return;
    AbstractAudioObject::updatePosition();
}

void CartSlot::fadeOutAllSlots(CartSlot *except, bool allowOthers)
{
    int fadeMs = Configuration::getInstance()->getSlotFade();
    QMapIterator<int, CartSlot*> i(audioObjects);
    while (i.hasNext()) {
        i.next();
        CartSlot *slot = i.value();
        if (except != NULL && slot == except)
            continue;
        if (slot->getLetFade() || allowOthers)
            slot->fadeOut(fadeMs);
    }
}

void CartSlot::saveInDatabase()
{
    CartSlot *tmp = this;
    int number = tmp->number;
    tmp->number = -1;
    tmp->database = true;
    tmp->saveData();
    tmp->number = number;
    tmp->database = false;
}

void CartSlot::loadFromDatabase(int id)
{
    int number = this->number;
    this->number = id;
    this->database = true;
    this->readData();
    this->database = false;
    this->number = number;
    this->saveData();
    this->fetchLength();
}

void CartSlot::loadFromSlot(int id)
{
    int number = this->number;
    this->number = id;
    this->readData();
    this->number = number;
    this->saveData();
    this->fetchLength();
}

void CartSlot::empty() {
    // this->filename = "";
    this->startPos = 0;
    this->stopPos = 0;
    this->length = 0;
    // this->text1 = "";
    this->loadStream();
    this->saveData();
    this->updatePosition();
}

void CartSlot::clearColor() {
    // this->fontColor = "#000000";
    // this->color = "#FFFFFF";

}

void CartSlot::loadEqualizer()
{
    eqs.clear();
    if (eqActive) {
        QList<QString> gains = eqConfig.split(";");
        if (gains.size() == 10) {
            int center = 16000;
            for (int i=0;i<10;i++) {
                BASS_DX8_PARAMEQ eq;
                eq.fGain = gains.at(i).toInt();
                eq.fCenter = center;
                eq.fBandwidth = 12;
                eqs.append(eq);
                center = center / 2;
            }
        }
    }
}

int CartSlot::isUsed(QString filename)
{
    foreach(int key, audioObjects.keys())
    {
        /*if (audioObjects.value(key)->getFileName() == filename) {
            return key;
        }*/
    }
    return -1;
}
