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

#ifndef OUTPUTSELECTIONWIDGET_H
#define OUTPUTSELECTIONWIDGET_H

#include <QWidget>

#include "audio_global.h"

namespace Audio {

class IDevice;

namespace Ui {
class OutputSelectionWidget;
} // namespace Ui

class AUDIO_EXPORT OutputSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OutputSelectionWidget(QWidget *parent = 0);
    ~OutputSelectionWidget();

    QString driver() const;
    int device() const;
    int channel() const;
    void setSelection(QString driver, int device, int channel);

private:
    Ui::OutputSelectionWidget *m_ui;
    QString m_driver;
    int m_device;
    IDevice *m_deviceInstance = 0;
    int m_channel;

private slots:
    void driverChanged(int index);
    void deviceChanged(int index);
    void channelCountChanged(int count);
};

} // namespace Audio

#endif // OUTPUTSELECTIONWIDGET_H
