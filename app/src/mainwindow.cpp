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

#include <QFileDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QProgressDialog>
#include <QSettings>
#include <QTimer>
#include <QWheelEvent>
#include <math.h>
#include "aboutdialog.h"
#include "bassmix.h"
#include "cartslotwidget.h"
#include "configurationdialog.h"
#include "mainwindow.h"
#include "audioprocessor.h"
#include "bassasiodevice.h"
#include "bassdevice.h"
#include "cartslot.h"
#include "playlistplayer.h"
#include "pluginloader.h"
#include "clearlayerthread.h"
#include "configuration.h"
#include "copycolorsthread.h"
#include "globaldata.h"
#include "keyboardcontroller.h"
#include "playlist.h"
#include "playerwidget.h"
#include "slotstoredialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->pauseModifier = false;
}

MainWindow::~MainWindow()
{
    AudioProcessor::getInstance()->freeDevices();
    AudioProcessor::dropInstance();
    KeyboardController::getInstance()->closeKeyboardController();
    delete ui;
}

void MainWindow::init() {
    ui->setupUi(this);

    ui->menuWidget->addButton(ui->slotAction);
    ui->menuWidget->addButton(ui->playlistAction);
    connect(ui->menuWidget, SIGNAL(currentTabChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    ui->menuWidget->selectFirstButton();

    createPlayers();

    fileModel = new QFileSystemModel();
    fileModel->setNameFilters(GlobalData::getSupportedAudioFormats(false));
    fileModel->setRootPath("/");
    fileModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    fileModel->setNameFilterDisables(false);
    //fileModel->setSupportedDragActions(Qt::CopyAction | Qt::MoveAction);
    ui->fileView->setModel(fileModel);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,9);
    ui->splitter_2->setStretchFactor(0,8);
    ui->splitter_2->setStretchFactor(1,2);
    this->showMaximized();
    connect(ui->configAction, SIGNAL(triggered()), this, SLOT(showConfigDialog()));
    connect(ui->aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(ui->autoPlayCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setAutoPlay()));
    connect(ui->playlistNextButton, SIGNAL(clicked()), Playlist::getInstance(), SLOT(fadeNext()));
    connect(ui->openButton, SIGNAL(clicked()), ui->playListTable, SLOT(openPlaylist()));
    connect(ui->saveButton, SIGNAL(clicked()), ui->playListTable, SLOT(savePlaylist()));
    connect(ui->layerSelector, SIGNAL(currentTabChanged(int)), this, SLOT(updateSlotAssignment()));
    connect(ui->saveHistoryButton, SIGNAL(clicked()), ui->historyList, SLOT(saveHistory()));
    connect(ui->slotStoreAction, SIGNAL(triggered()), this, SLOT(showSlotStore()));
    connect(ui->colorAction, SIGNAL(triggered()), this, SLOT(copyColors()));
    connect(ui->clearLayerAction, SIGNAL(triggered()), this, SLOT(clearSlots()));
    connect(ui->setConfigurationAction, SIGNAL(triggered()), this, SLOT(setConfigDirectory()));
}

void MainWindow::createPlayers()
{
    Configuration *config = Configuration::getInstance();
    int layers = config->getLayer();
    ui->layerSelector->setLayerCount(layers);
    int currentLayer = ui->layerSelector->getSelectedButton();
    foreach(CartSlotWidget *cartSlotWidget,slotWidgets)
    {
        ui->slotLayout->removeWidget(cartSlotWidget);
        cartSlotWidget->~CartSlotWidget();
    }
    slotWidgets.clear();
    foreach(PlayerWidget *playerWidget,playerWidgets)
    {
        ui->playerLayout->removeWidget(playerWidget);
        disconnect(playerWidget,0,0,0);
        playerWidget->~PlayerWidget();
    }
    slotWidgets.clear();
    playerWidgets.clear();

    int number=1+currentLayer*config->getVerticalSlots()*config->getHorizontalSlots();
    for (int i=0;i<config->getVerticalSlots();i++)
    {
        for (int j=0;j<config->getHorizontalSlots();j++)
        {
            CartSlotWidget *newWidget = new CartSlotWidget(number);
            ui->slotLayout->addWidget(newWidget,i,j);
            slotWidgets.append(newWidget);
            number++;
        }
    }

    for (int i=0;i<config->getPlayer();i++)
    {
        PlayerWidget *newWidget = new PlayerWidget(i+1);
        connect(newWidget,SIGNAL(addToHistory(PlaylistEntry*)),ui->historyList, SLOT(addPlaylistItem(PlaylistEntry*)));
        ui->playerLayout->addWidget(newWidget);
        playerWidgets.append(newWidget);
    }
}

void MainWindow::updateSlotAssignment()
{
    Configuration *config = Configuration::getInstance();
    int currentLayer = ui->layerSelector->getSelectedButton();
    int number=1+currentLayer*config->getVerticalSlots()*config->getHorizontalSlots();
    for (int i=0;i<slotWidgets.size();i++) {
        int displayNumber;
        if (config->getLayerKeyboardSync()) {
            displayNumber = i+1;
        } else {
            displayNumber = number;
        }
        slotWidgets.at(i)->setNewNumber(number,true,displayNumber);
        number++;
    }
}

void MainWindow::showConfigDialog()
{
    ConfigurationDialog *configDialog = new ConfigurationDialog(this);
    if (configDialog->exec()==1)
    {
        ui->layerSelector->selectFirstButton();
        createPlayers();
    }
}

void MainWindow::setAutoPlay()
{
    Playlist::getInstance()->setAutoPlay(ui->autoPlayCheckBox->isChecked());
}

void MainWindow::showBassErrorMessage(int code)
{
    QString message="";
    switch (code)
    {
    case 3: message = tr("Der Treiber ist nicht verfügbar. Eventuell wird das Audiogerät schon benutzt."); break;
    case 8: message = tr("Ein Ausgabekanal konnte nicht angewählt werden, weil er nicht initialisert wurde. Entweder ist die entsprechende Soundkarte nicht angeschlossen oder die entsprechenden Funktionen (z.B. ASIO-Gerät) sind in ihrem Programm nicht aktiviert."); break;
    case 23: message = tr("Das ausgewählte Audiogerät ist nicht vorhanden."); break;
    default: message = QString::number(code);
    }
    showErrorMessage(message);
}

void MainWindow::showErrorMessage(QString message)
{
    QMessageBox::critical(this,tr("Fehler"),message);
}

void MainWindow::keyboardSignal(int key, int pressed)
{
    Configuration *conf = Configuration::getInstance();
    if (pressed==0) //pressed
    {
        if (key==122) {
            int layer = ui->layerSelector->getSelectedButton();
            if (layer >= 1)
                ui->layerSelector->selectButtonAt(layer-1);
        } else if (key==123) {
            int layer = ui->layerSelector->getSelectedButton();
            if (layer <= conf->getLayer()-2)
                ui->layerSelector->selectButtonAt(layer+1);
        } else if (key==124) {
            ui->menuWidget->selectButtonAt((ui->menuWidget->getSelectedButton()+1)%2);
        } else if (key==125) {
            ui->autoPlayCheckBox->setChecked(!ui->autoPlayCheckBox->isChecked());
        } else if (key==126) {
            Playlist::getInstance()->fadeNext();
        } else if (key==127) {
            this->pauseModifier = true;
        } else if (key==128) {
            CartSlot::fadeOutAllSlots(NULL,true);
            PlaylistPlayer::fadeOutAllPlayers();
        } else if (key<=(conf->getHorizontalSlots()*conf->getVerticalSlots())) {
            int key2 = key;
            if (conf->getLayerKeyboardSync()) {
                key2 += (conf->getHorizontalSlots()*conf->getVerticalSlots()*ui->layerSelector->getSelectedButton());
            } else {
                ui->layerSelector->selectButtonAt(0);
            }
            CartSlot *slot = AudioProcessor::getInstance()->getCartSlotWithNumber(key2);
            if (pauseModifier) {
                slot->pause();
            } else {
                slot->play();
            }
            ui->stackedWidget->setCurrentIndex(0);
        } else if (key >= 116 && key <= 121) {
            ui->layerSelector->selectButtonAt(key-116);
        } else {
            int id = floor((double)key-109-((double)key-110)/2);
            if (key%2 ==0) //start
            {
                AudioProcessor::getInstance()->getPlayerWithNumber(id)->play();
                ui->stackedWidget->setCurrentIndex(1);
            }
            else //stop
            {
                AudioProcessor::getInstance()->getPlayerWithNumber(id)->stop();
            }
        }
    } else {
        if (key==127) {
            this->pauseModifier = false;
        }
    }
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    Configuration *conf = Configuration::getInstance();
    int numDegrees = e->delta() / 8;
    int numSteps = numDegrees / 15;
    int currentIndex = ui->layerSelector->getSelectedButton();
    int layerCount = conf->getLayer();
    if (numSteps > 0)
    {
        currentIndex = qMax(0,currentIndex-numSteps);
    }
    else
    {
        currentIndex = qMin(layerCount-1,currentIndex-numSteps);
    }
    ui->layerSelector->selectButtonAt(currentIndex);
}

void MainWindow::showAbout()
{
    AboutDialog *dia = new AboutDialog(this);
    dia->exec();
}

void MainWindow::showSlotStore()
{
    SlotStoreDialog *ssd = new SlotStoreDialog(this);
    ssd->show();
}

void MainWindow::copyColors() {
    int res = QMessageBox::question(this,tr("Wirklich kopieren?"),tr("Sollen die Farben wirklich kopiert werden?"),QMessageBox::Yes,QMessageBox::No);
    if (res == QMessageBox::No) {
        return;
    }
    CopyColorsThread *copy = new CopyColorsThread(ui->layerSelector->getSelectedButton());
    QProgressDialog *dia = new QProgressDialog(this);
    dia->setCancelButton(NULL);
    dia->setLabelText(tr("Farben kopieren...."));
    dia->setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    connect(copy,SIGNAL(updateStatus(int)), dia, SLOT(setValue(int)));
    connect(copy,SIGNAL(updateMax(int)), dia, SLOT(setMaximum(int)));
    connect(dia,SIGNAL(canceled()), copy, SLOT(quit()));
    copy->start();
    dia->exec();
}

void MainWindow::clearSlots() {
    int res = QMessageBox::question(this,tr("Wirklich löschen?"),tr("Sollen alle Slots in diesem Layer entfernt werden?"),QMessageBox::Yes,QMessageBox::No);
    if (res == QMessageBox::No) {
        return;
    }
    ClearLayerThread *clear = new ClearLayerThread(ui->layerSelector->getSelectedButton());
    QProgressDialog *dia = new QProgressDialog(this);
    dia->setCancelButton(NULL);
    dia->setLabelText(tr("Layer löschen...."));
    dia->setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    connect(clear,SIGNAL(updateStatus(int)), dia, SLOT(setValue(int)));
    connect(clear,SIGNAL(updateMax(int)), dia, SLOT(setMaximum(int)));
    connect(dia,SIGNAL(canceled()), clear, SLOT(quit()));
    clear->start();
    dia->exec();
    foreach(CartSlotWidget *cartSlotWidget,slotWidgets)
    {
        cartSlotWidget->updateLength(0);
        cartSlotWidget->updatePosition(0);
        cartSlotWidget->showInfo();
	}
}

void MainWindow::setConfigDirectory()
{
    QFileDialog dia(this);
    dia.setViewMode(QFileDialog::List);
    dia.setFileMode(QFileDialog::Directory);
    dia.setAcceptMode(QFileDialog::AcceptOpen);
    dia.setOptions(QFileDialog::ShowDirsOnly);
    dia.setDirectory(QDir(Configuration::getStorageLocation()));
    dia.setWindowTitle(QObject::tr("Bitte selektieren Sie einen Ordner in dem die Konfigurations-Dateien abgelegt werden sollen."));
    if (dia.exec() == 1) {
        Configuration::setStorageLocation(dia.selectedFiles().at(0));
        QMessageBox::information(this,tr("Konfiguration aktualisiert"),tr("Bitte starten Sie das Programm neu um die neuen Daten zu laden."));
    }
}
