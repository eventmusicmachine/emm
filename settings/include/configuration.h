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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QMap>
#include <QObject>

class Configuration : public QObject
{
    Q_OBJECT
public:
    int getPlayer();
    int getPlaylistFade();
    int getSlotFade();
    int getPlaylistFPos();
    bool getLayerKeyboardSync();
    bool getPauseButton();
    int getSlotTimeSize();
    void setPlayer(int player);
    void setPlaylistFade(int playlistFade);
    void setSlotFade(int slotFade);
    void setPlaylistFPos(int playlistFPos);
    void setLayerKeyboardSync(bool layerKeyboardSync);
    void setPauseButton(bool pauseButton);
    void setSlotTimeSize(int size);
    void saveData();
    static void setStorageLocation(QString location);
    static QString getStorageLocation();
    static Configuration* getInstance();
    static void dropInstance();

private:
    Configuration() {}
    Configuration(const Configuration &);
    Configuration& operator=(const Configuration &);
    static Configuration* instance;

    int player;
    int playlistFade;
    int playlistFPos;
    int slotFade;
    int slotTimeSize;
    bool layerKeyboardSync;
    bool pauseButton;

    void readData();

};

#endif // CONFIGURATION_H
