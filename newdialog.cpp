/*
 * Fraqter - a fractal exploration program
 * Copyright (C) 2019 Johan Thelin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "newdialog.h"
#include "ui_newdialog.h"

#include <QItemSelectionModel>
#include <QPushButton>

#include "mainwindow.h"

NewDialog::NewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDialog)
{
    m_fractalNames.setStringList(QStringList() << tr("Mandelbrot") << tr("Julia"));

    ui->setupUi(this);
    ui->listViewFractals->setModel(&m_fractalNames);

    connect(ui->listViewFractals->selectionModel(), &QItemSelectionModel::selectionChanged, this, &NewDialog::onFractalChanged);
    connect(ui->listViewFractals, &QAbstractItemView::doubleClicked, this, &NewDialog::onDoubleClickedItem);
    connect(this, &QDialog::accepted, this, &NewDialog::onAccepted);

    if (ui->listViewFractals->model()->rowCount() > 0)
        ui->listViewFractals->setCurrentIndex(ui->listViewFractals->model()->index(0,0));
    else
        onFractalChanged(ui->listViewFractals->selectionModel()->selection());
}

NewDialog::~NewDialog()
{
    delete ui;
}

void NewDialog::onFractalChanged(const QItemSelection &selection)
{
    if (selection.isEmpty())
    {
        ui->labelName->setText("");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else
    {
        ui->labelName->setText(ui->listViewFractals->model()->data(selection.indexes().first()).toString());
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void NewDialog::onDoubleClickedItem(const QModelIndex &)
{
    accept();
}

void NewDialog::onAccepted()
{
    MainWindow *mainWindow = new MainWindow(ui->listViewFractals->model()->data(ui->listViewFractals->selectionModel()->selection().indexes().first()).toString());
    mainWindow->show();
}
