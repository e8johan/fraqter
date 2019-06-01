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
#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>

#include <QStringListModel>
#include <QItemSelection>

namespace Ui {
class NewDialog;
}

class NewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDialog(QWidget *parent = nullptr);
    ~NewDialog();

private slots:
    void onAccepted();
    void onFractalChanged(const QItemSelection &);
    void onDoubleClickedItem(const QModelIndex &index);

private:
    Ui::NewDialog *ui;
};

#endif // NEWDIALOG_H
