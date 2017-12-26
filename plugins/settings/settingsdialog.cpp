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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "navigationtreemodel.h"
#include "isettingspagefactory.h"
#include "isettingspage.h"

using namespace Settings;
using namespace Settings::Internal;

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    m_model(new NavigationTreeModel),
    m_ui(new Ui::SettingsDialog)
{
    m_ui->setupUi(this);

    QList<int> splitterSizes;
    splitterSizes << 200 << 500;
    m_ui->splitter->setSizes(splitterSizes);

    m_ui->navigationTree->setModel(m_model);

    connect(m_ui->navigationTree->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(showSettingsWidget(QModelIndex)));
}

SettingsDialog::~SettingsDialog()
{
    delete m_ui;
    delete m_model;
}

void SettingsDialog::showSettingsWidget(const QModelIndex &selected)
{
    if (selected.isValid()) {
        ISettingsPageFactory *factory = m_model->factory(selected);
        if (factory) {
            ISettingsPage *page = factory->createPage();
            if (m_page) {
                QLayoutItem *item = m_ui->contentLayout->replaceWidget(m_page->widget(), page->widget());
                delete item;
                delete m_page;
                m_page = page;
            } else {
                m_ui->contentLayout->addWidget(page->widget());
                m_page = page;
            }
        }
    }
}
