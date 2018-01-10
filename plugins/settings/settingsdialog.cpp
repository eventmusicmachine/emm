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
    m_ui(new Ui::SettingsDialog),
    m_model(new NavigationTreeModel)
{
    m_ui->setupUi(this);

    QList<int> splitterSizes;
    splitterSizes << 200 << 500;
    m_ui->splitter->setSizes(splitterSizes);

    m_ui->navigationTree->setModel(m_model);

    connect(m_ui->navigationTree->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &SettingsDialog::showSettingsWidget);
    connect(m_ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);
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
            m_visitedPages.append(page);
            if (m_page) {
                QLayoutItem *item = m_ui->contentLayout->replaceWidget(m_page, page);
                delete item;
                delete m_page;
                m_page = page;
            } else {
                m_ui->contentLayout->addWidget(page);
                m_page = page;
            }
            m_page->load();
        }
    }
}

void SettingsDialog::accept()
{
    foreach (ISettingsPage *page, m_visitedPages) {
        page->apply();
    }
    done(QDialog::Accepted);
}
