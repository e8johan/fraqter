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
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "newdialog.h"

#include "fractalmandelbrot.h"
#include "fractaljulia.h"

MainWindow::MainWindow(const QString &fractalId, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (fractalId == "Mandelbrot")
        m_fractalView = new FractalMandelbrot(this);
    else
        m_fractalView = new FractalJulia(this);

    setCentralWidget(m_fractalView);

    connect(ui->actionFileNew, &QAction::triggered, this, &MainWindow::onNew);
    connect(ui->actionFileExit, &QAction::triggered, qApp, &QCoreApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNew()
{
    NewDialog newDialog(this);
    newDialog.exec();
}
