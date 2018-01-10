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

#include "bassdevice.h"
#include "bassmix.h"
#include "configuration.h"

void BassDevice::init()
{
    /* if (!BASS_Init(deviceID,44100,0,(HWND)mainwindow->winId(),NULL)) {
        emit errorOccured(BASS_ErrorGetCode());
    }
    else
    {
        if (!this->setOutputDevice())
            return;

        channelCount = getInfo().speakers/2;
        for (int a=0;a<channelCount;a++) {
            HSTREAM newMixer = BASS_Mixer_StreamCreate(44100,2, BASS_SAMPLE_FLOAT | getSpeakerFlag(a+1));
            streams.append(newMixer);
            BASS_ChannelPlay(newMixer,false);
        }
    } */
}

/*void BassDevice::initialize()
{
    BASS_SetConfig(BASS_CONFIG_BUFFER,Configuration::getInstance()->getSlotBuffer());
}*/

DWORD BassDevice::getSpeakerFlag(int channel)
{
    switch (channel)
    {
    case 1: return BASS_SPEAKER_FRONT;
    case 2: return BASS_SPEAKER_CENLFE;
    case 3: return BASS_SPEAKER_REAR;
    case 4: return BASS_SPEAKER_REAR2;
    }
    return BASS_SPEAKER_FRONT;
}
