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

#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include "editcartslotdialog.h"
#include "model/slottablemodel.h"
#include "slotstoredialog.h"
#include "ui_slotstoredialog.h"

#include "model/audio/audioprocessor.h"
#include "model/audio/bassasiodevice.h"
#include "model/audio/bassdevice.h"
#include "model/audio/cartslot.h"
#include "model/audio/pflplayer.h"

SlotStoreDialog::SlotStoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SlotStoreDialog)
{

    player = AudioProcessor::getInstance()->getPFLPlayer();

    this->title = "";

    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool);
    model = new SlotTableModel();
    model->loadData();
    sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(model);
    ui->storeTable->setModel(sortModel);
    ui->storeTable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->storeTable->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    ui->storeTable->horizontalHeader()->setSectionResizeMode(5,QHeaderView::Stretch);
    ui->storeTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->storeTable->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->storeTable->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);
    ui->storeTable->horizontalHeader()->resizeSection(1,25);
    ui->storeTable->horizontalHeader()->resizeSection(2,25);
    ui->storeTable->horizontalHeader()->resizeSection(4,45);
    connect(ui->controlBar, SIGNAL(addClicked()), this, SLOT(addSlot()));
    connect(ui->controlBar, SIGNAL(editClicked()), this, SLOT(editSlot()));
    connect(ui->controlBar, SIGNAL(removeClicked()), this, SLOT(removeSlot()));
    connect(ui->controlBar, SIGNAL(playClicked()), this, SLOT(playSlot()));
    connect(ui->controlBar, SIGNAL(stopClicked()), this, SLOT(stopSlot()));
    //connect(ui->controlBar, SIGNAL(playClicked()), player, SLOT(play()));
    //connect(ui->controlBar, SIGNAL(stopClicked()), player, SLOT(stop()));
    connect(ui->storeTable, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editSlot(QModelIndex)));

    connect(player, SIGNAL(sendName(QString)), this, SLOT(setTitle(QString)));

    // m2: allow drag and drop files
    setAcceptDrops(true);
}

SlotStoreDialog::~SlotStoreDialog()
{
    delete ui;
}

void SlotStoreDialog::addSlot()
{
    EditCartSlotDialog *ecsd = new EditCartSlotDialog(-1,true);
    if (ecsd->exec())
    {
        model->loadData();
    }
}

void SlotStoreDialog::editSlot()
{
    QModelIndex index = sortModel->index(ui->storeTable->currentIndex().row(),0);
    editSlot(index);
}

void SlotStoreDialog::editSlot(QModelIndex index)
{
    if (!index.isValid())
        return;
    index = sortModel->mapToSource(index);
    int row = index.row();
    QModelIndex idx = model->index(row,0);
    int id = model->data(idx,Qt::DisplayRole).toInt();
    EditCartSlotDialog *ecsd = new EditCartSlotDialog(id,true);
    if (ecsd->exec())
    {
        model->loadData();
    }
}

void SlotStoreDialog::removeSlot()
{
    QModelIndex index = sortModel->index(ui->storeTable->currentIndex().row(),0);
    if (!index.isValid())
        return;
    index = sortModel->mapToSource(index);
    int id = model->data(index,Qt::DisplayRole).toInt();
    model->removeWithId(id);
    model->loadData();
}

// m2: Play title currently selected
void SlotStoreDialog::playSlot()
{
    // Get ID field (0) of selected row
    QModelIndex index = sortModel->index(ui->storeTable->currentIndex().row(), 0);

    // Get SlotID field (4) of selected row
    QModelIndex indexSlotID = sortModel->index(ui->storeTable->currentIndex().row(), 4);

    // Get Filename field (5) of selected row
    QModelIndex indexFilename = sortModel->index(ui->storeTable->currentIndex().row(), 5);

    if (!index.isValid())
        return;

    index = sortModel->mapToSource(index);
    int id = model->data(index, Qt::DisplayRole).toInt();

    QString filename = model->data(indexFilename, Qt::DisplayRole).toString();

    // If SlotID = "X" => id = 0

    qDebug() << QString("Selected slot: %1").arg(id);


    id = ui->storeTable->currentIndex().row();
    model->playWithId(id);
}


// m2: Stop title currently selected
void SlotStoreDialog::stopSlot()
{
    int id = ui->storeTable->currentIndex().row();
    model->stopWithId(id);
}

// m2: drag & drop files
void SlotStoreDialog::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

// m2: drag & drop files
void SlotStoreDialog::dropEvent(QDropEvent *e)
{
    // TODO do it in a parallel thread with progress bar and possibility to stop
    //ClearLayerThread *clear = new ClearLayerThread(ui->layerSelector->getSelectedButton());
    //QProgressDialog *dia = new QProgressDialog(this);
    //dia->setCancelButton(NULL);
    //dia->setLabelText(tr("Layer löschen...."));
    //dia->setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    //connect(clear,SIGNAL(updateStatus(int)), dia, SLOT(setValue(int)));
    //connect(clear,SIGNAL(updateMax(int)), dia, SLOT(setMaximum(int)));
    //connect(dia,SIGNAL(canceled()), clear, SLOT(quit()));
    //clear->start();
    //dia->exec();

    // Add slots from dragged&dropped files
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        qDebug() << "Dropped file:" << fileName;
        this->addSlotAuto(fileName);
    }
}

void SlotStoreDialog::addSlotAuto(QString filename)
{

    player->setFilename(filename);
    player->analyse(true);

    CartSlot *slot = CartSlot::getObjectWithNumber(-1, true);

    int type = 0;
    int device = 0;
    int channel = 1;
    QString color = "#FFFFFF";
    QString fontColor = "#000000";
    bool fadeOut = true;
    bool letFade = true;
    bool fadeOthers = true;
    bool loop = false;
    double startPos = 0;
    double stopPos = 0;
    int pitch = 0;
    int fontSize = 14;
    int db = 0;
    bool eqActive = false;
    QString eqConfig = "0;0;0;0;0;0;0;0;0;0";
    bool pauseDisabled = false;

    slot->setDataAndSave(
        filename,
        this->title,
        type,
        device,
        channel,
        color,
        fontColor,
        fadeOut,
        letFade,
        fadeOthers,
        loop,
        startPos,
        stopPos,
        pitch,
        fontSize,
        db,
        eqActive,
        eqConfig,
        // m2: new checkbox disable pause
        pauseDisabled
    );

    model->loadData();
}

void SlotStoreDialog::setTitle(QString name)
{
    this->title = name;
}

