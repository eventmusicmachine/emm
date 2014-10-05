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

#include <QDrag>
#include <QDropEvent>
#include <QMessageBox>
#include <QMimeData>
#include <QMouseEvent>
#include <math.h>
#include "cartslot.h"
#include "cartslotwidget.h"
#include "editcartslotdialog.h"
#include "audioprocessor.h"
#include "configuration.h"
#include "globaldata.h"
#include "ui_cartslotwidget.h"

CartSlotWidget::CartSlotWidget(int number, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartSlotWidget)
{
    ui->setupUi(this);
    ui->contentWidget->setBackgroundRole(QPalette::Background);
    this->setNewNumber(number,false);
    this->setAcceptDrops(true);
    ui->pauseButton->setVisible(false);
}

CartSlotWidget::~CartSlotWidget()
{
    delete ui;
}

void CartSlotWidget::setNewNumber(int number, bool dis, int displayNumber)
{
    if (displayNumber == -1) {
        displayNumber = number;
    }
    ui->editButton->setText(QString::number(displayNumber));
    this->slotNumber = number;
    if (dis) {
        disconnect(slot,0,0,0);
        disconnect(ui->pauseButton, 0, 0, 0);
    }
    this->slot = AudioProcessor::getInstance()->getCartSlotWithNumber(number);
    showInfo();
    ui->progressBar->setValue(100);
    ui->pauseButton->setVisible(slot->isPlaying() || slot->isPaused());
    connect(slot, SIGNAL(sendSongLength(double)), this, SLOT(updateLength(double)));
    connect(slot, SIGNAL(sendCurrentPosition(double)), this, SLOT(updatePosition(double)));
    connect(slot, SIGNAL(stopped()), this, SLOT(stoppedPlaying()));
    connect(slot, SIGNAL(startedPlaying()), this, SLOT(startedPlaying()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pauseSlot()));
    updateLength(slot->getLength());
}

void CartSlotWidget::showInfo()
{
    this->normalColor = GlobalData::getColorCode(slot->getColor());
    QColor col = QColor(this->normalColor);
    int r,g,b;
    col.getRgb(&r,&g,&b);
    QColor col2;
    col2.setRgb(255-r,255-g,255-b);
    this->blinkColor = col2.name();

    this->normalFontColor = slot->getFontColor();
    QColor col3 = QColor(this->normalFontColor);
    col3.getRgb(&r,&g,&b);
    QColor col4;
    col4.setRgb(255-r,255-g,255-b);
    this->blinkFontColor = col4.name();

    ui->text1Label->setText("<center>"+slot->getText1()+"</center>");

    QFont font = ui->text1Label->font();
    font.setPixelSize(slot->getFontSize());
    font.setBold(true);
    ui->text1Label->setFont(font);

    QPalette p(ui->text1Label->palette());
    p.setColor(QPalette::Text,QColor(this->normalFontColor));

    ui->text1Label->setPalette(p);
    ui->toPlayLabel->setPalette(p);
    QFont font2 = ui->toPlayLabel->font();
    font2.setPixelSize(Configuration::getInstance()->getSlotTimeSize());
    ui->toPlayLabel->setFont(font2);

    this->setColor();
    slot->loadEqualizer();
}

void CartSlotWidget::setColor(bool blink)
{
    QString color,fontColor;
    if (blink) {
        color = this->blinkColor;
        fontColor = this->blinkFontColor;
    } else {
        color = this->normalColor;
        fontColor = this->normalFontColor;
    }
    QPalette p(ui->contentWidget->palette());
    p.setColor(QPalette::Background, QColor(color));
    ui->contentWidget->setPalette(p);

    QPalette t(ui->text1Label->palette());
    t.setColor(QPalette::Text, QColor(fontColor));
    t.setColor(QPalette::Foreground, QColor(fontColor));
    ui->text1Label->setPalette(t);
    ui->toPlayLabel->setPalette(t);
}

void CartSlotWidget::editCartSlot()
{
    EditCartSlotDialog *editDialog = new EditCartSlotDialog(this->slotNumber);
    if (editDialog->exec()==1) {
        slot->fetchLength();
        showInfo();
        this->stoppedPlaying();
    }
}

void CartSlotWidget::updateLength(double length)
{
    this->length = length;
    if (length > 0) {
        ui->progressBar->setMaximum(length);
        ui->progressBar->setValue(length);
    }
}

void CartSlotWidget::updatePosition(double pos)
{
    double pos2 = (length-pos);
    int mins2 = pos2/60;
    int secs2 = floor(pos2-mins2*60);
    int msecs2 = floor((pos2-mins2*60-secs2)*10);
    ui->progressBar->setValue(length-pos);
    QString time = QString("%1:%2.%3").arg(mins2,2, 10, QChar('0')).arg(secs2,2,10, QChar('0')).arg(msecs2);
    ui->toPlayLabel->setText(time);
    if (secs2%2==0)
    {
        this->setColor(true);
    }
    else
    {
        this->setColor(false);
    }
}

void CartSlotWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->modifiers() == Qt::ShiftModifier) {
        slot->pause();
    } else if (e->modifiers() == Qt::ControlModifier) {
        QDrag *dr = new QDrag(this);
        QMimeData *mimeData = new QMimeData();
        int id = slot->getNumber();
        QByteArray encodedData = QByteArray::number(id);
        mimeData->setData("application/emm.store.slotid",encodedData);
        dr->setMimeData(mimeData);
        dr->start();
    } else if (e->modifiers() == Qt::AltModifier) {
        int res = QMessageBox::question(this,tr("Wirklich löschen?"),tr("Soll der Slot wirklich gelöscht werden?"),QMessageBox::Yes,QMessageBox::No);
        if (res == QMessageBox::Yes) {
            slot->empty();
            showInfo();
        }
    } else {
        if (e->button() == Qt::LeftButton)
            slot->play();
        else
            editCartSlot();
    }
}

void CartSlotWidget::stoppedPlaying()
{
    updateLength(slot->getLength());
    updatePosition(0);
    ui->progressBar->setValue(ui->progressBar->maximum());
    this->setColor();
    ui->pauseButton->setVisible(false);
}

void CartSlotWidget::startedPlaying()
{
    if (Configuration::getInstance()->getPauseButton()) {
        ui->pauseButton->setVisible(true);
    }
}

void CartSlotWidget::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->formats().contains("application/emm.store.objectid") ||
        e->mimeData()->formats().contains("application/emm.store.slotid"))
        e->acceptProposedAction();
}

void CartSlotWidget::dragMoveEvent(QDragMoveEvent *e)
{
    if (e->mimeData()->formats().contains("application/emm.store.objectid") ||
        e->mimeData()->formats().contains("application/emm.store.slotid"))
        e->accept();
}

void CartSlotWidget::dropEvent(QDropEvent *e)
{
    if (e->mimeData()->formats().contains("application/emm.store.objectid") && e->proposedAction() == Qt::CopyAction) {
        int id = QString(e->mimeData()->data("application/emm.store.objectid")).toInt();
        slot->loadFromDatabase(id);
    } else if (e->mimeData()->formats().contains("application/emm.store.slotid") && e->proposedAction() == Qt::CopyAction) {
        int id = QString(e->mimeData()->data("application/emm.store.slotid")).toInt();
        slot->loadFromSlot(id);
    }
    showInfo();
    stoppedPlaying();
}

void CartSlotWidget::pauseSlot()
{
    slot->pause();
}
