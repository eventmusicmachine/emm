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

#include <QMessageBox>
#include "configurationdialog.h"
#include "configuration.h"
#include "ui_configurationdialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);

    ui->menuTree->setCurrentItem(ui->menuTree->topLevelItem(0));

    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(saveAndClose()));

    Configuration *config = Configuration::getInstance();
    ui->playerSpinBox->setValue(config->getPlayer());
    ui->playlistFadeSpinBox->setValue(config->getPlaylistFade());
    ui->slotFadeSpinBox->setValue(config->getSlotFade());
    ui->keyboardSyncCheckBox->setChecked(config->getLayerKeyboardSync());
    ui->playlistFadePosSpinBox->setValue(config->getPlaylistFPos());
    ui->slotTimeSpinBox->setValue(config->getSlotTimeSize());
    ui->pauseCheckBox->setChecked(config->getPauseButton());
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::closeWindow()
{
    done(0);
}

void ConfigurationDialog::saveAndClose()
{
    /* if (ui->horizontalSpinBox->value()*ui->verticalSpinBox->value()>109){
        QMessageBox::information(this,tr("Zu viele Slots"),tr("Es können maximal 109 Slots pro Layer angelegt werden."));
        return;
    } */
    Configuration *config = Configuration::getInstance();
    config->setPlayer(ui->playerSpinBox->value());
    config->setPlaylistFade(ui->playlistFadeSpinBox->value());
    config->setSlotFade(ui->slotFadeSpinBox->value());
    config->setLayerKeyboardSync(ui->keyboardSyncCheckBox->isChecked());
    config->setPlaylistFPos(ui->playlistFadePosSpinBox->value());
    config->setSlotTimeSize(ui->slotTimeSpinBox->value());
    config->setPauseButton(ui->pauseCheckBox->isChecked());
    config->saveData();
    done(1);
}
