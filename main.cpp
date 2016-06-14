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

#include <QApplication>
#include <QBitmap>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <QSqlDatabase>
#include <QTimer>
#include <stdio.h>
#include "model/audio/audioprocessor.h"
#include "model/audio/cartslot.h"
#include "model/audio/pluginloader.h"
#include "model/configuration.h"
#include "model/keyboardcontroller.h"
#include "view/mainwindow.h"
#include "view/splashscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QPixmap pixmap(":/icons/splash.png");

    SplashScreen *s = new SplashScreen(pixmap);
    s->show();
    s->showMessage("Event Music Machine starten...");

    // Make sure splash is drawn
    a.processEvents();

    QString path = Configuration::getStorageLocation();
    if (path == "") {
        QFileDialog dia(s);
        dia.setViewMode(QFileDialog::List);
        dia.setFileMode(QFileDialog::Directory);
        dia.setAcceptMode(QFileDialog::AcceptOpen);
        dia.setOptions(QFileDialog::ShowDirsOnly);
        dia.setWindowTitle(QObject::tr("Bitte selektieren Sie einen Ordner in dem die Konfigurations-Dateien abgelegt werden sollen."));
        if (dia.exec() == 1) {
            path = dia.selectedFiles().at(0);
            Configuration::setStorageLocation(path);
        }
    }

    s->showMessage("Slotspeicher verbinden...");
    if (!QFile(Configuration::getStorageLocation() + "/slotstore.emm").exists())
    {
        QMessageBox::information(s,"Slot-Speicher anlegen",QObject::tr("Es wurde keine gültige Slot-Datenbank gefunden. Sie wurde jetzt angelegt."));
        QFile::copy(":/slot-store.sqlite", Configuration::getStorageLocation() + "/slotstore.emm");
        QFile::setPermissions(Configuration::getStorageLocation() + "/slotstore.emm",QFile::ReadOther | QFile::WriteOther);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Configuration::getStorageLocation() + "/slotstore.emm");
    if (!db.open())
    {
        QMessageBox::warning(s,QObject::tr("Keine Verbindung zum Slot-Speicher"),QObject::tr("Es konnte keine Verbindung zum Slot-Speicher hergestellt werden!"));
    }

    s->showMessage("Verbindung zur Tastatur herstellen...");
    KeyboardController *keyController = KeyboardController::getInstance();
    QObject::connect(keyController, SIGNAL(errorOccured(QString)), s, SLOT(showErrorMessage(QString)));
    QObject::connect(keyController, SIGNAL(keyPressed(int,int)), &w, SLOT(keyboardSignal(int,int)));
    //keyController->initializeKeyboardController();
    bool retry = false;
    do {
        retry = false;
        int keyErr = keyController->initializeKeyboardController();
        if (keyErr == 1)
            QMessageBox::information(s,QObject::tr("EMM"),QObject::tr("Der Treiber für die Preh-Tastatur ist nicht installiert. Die Steuerung durch die Preh-Tastatur wird deaktiviert."));
        else if (keyErr == 2)
            QMessageBox::warning(s,QObject::tr("EMM"),QObject::tr("Die Preh-Tastatur konnte nicht initialisiert werden. Die Steuerung durch die Preh-Tastatur wird deaktiviert."));
        else if (keyErr == 3) {
            //QMessageBox::warning(s,QObject::tr("EMM"),QObject::tr("Die Verbindung zur Preh-Tastatur konnte nicht hergestellt werden. Bitte vergewissern Sie sich, dass die Preh-Tastatur korrekt angeschlossen ist und starten Sie danach das Programm neu."));
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(s, QString::fromUtf8("Preh-Tastatur nicht gefunden"), "Es wurde keine Preh-Tastatur gefunden, soll nochmals gesucht werden?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes)
                retry = true;
        }
    } while (retry);

    s->showMessage("Audiogeräte initialisieren...");

    AudioProcessor::getInstance()->initDevices(&w);

    s->showMessage("Audio-Plugins laden...");
    PluginLoader::loadPlugins();

    s->showMessage("Slots laden und überprüfen...");

    int number = 1;
    Configuration *config = Configuration::getInstance();
    for (int i=0;i<config->getLayer();i++)
    {
        for (int j=0;j<config->getVerticalSlots();j++)
        {
            for (int k=0;k<config->getHorizontalSlots();k++)
            {
                CartSlot *slot = AudioProcessor::getInstance()->getCartSlotWithNumber(number);
                s->showMessage("Slots laden und überprüfen...\r\n"+slot->getText1());
                if (slot->isMissing()) {
                    //QMessageBox::information(s,"Datei wurde nicht gefunden","Slot "+QString::number(slot->getNumber())+" ("+slot->getText1()+") konnte nicht geladen werden, weil die Datei nicht gefunden wurde!");

                    // m2: Ask user whether to ignore further "missing files"
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::question(s, QString::fromUtf8("Datei nicht gefunden"), "Slot "+QString::number(slot->getNumber())+" ("+slot->getText1()+") konnte nicht geladen werden, weil die Datei nicht gefunden wurde! \n \n Sollen weitere Meldungen angezeigt werden?", QMessageBox::Yes|QMessageBox::No);
                    if (reply == QMessageBox::No) {
                        k = config->getHorizontalSlots();
                        j = config->getVerticalSlots();
                        i = config->getLayer();
                    }
                }
                number++;
            }
        }
    }
    s->showMessage("Benutzeroberfläche initialisieren...");
    w.init();
    s->close();

    w.show();
    return a.exec();
}
