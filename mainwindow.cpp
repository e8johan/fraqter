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

#include <QMetaObject>
#include <QMetaProperty>

#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QStatusBar>
#include <QCheckBox>
#include <QPushButton>

#include "newdialog.h"

#include "fractalfactory.h"
#include "abstractfractalview.h"

MainWindow::MainWindow(const QString &fractalId, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_fractalView = FractalFactory::instance()->createView(fractalId);
    setCentralWidget(m_fractalView);

    ui->statusBar->addWidget(m_statusLabel = new QLabel(), 1);

    QFormLayout *layout = new QFormLayout(ui->propertiesDockContents);
    ui->propertiesDockContents->setLayout(layout);

    const QMetaObject *mo = m_fractalView->metaObject();
    int firstIndex = AbstractFractalView::staticMetaObject.propertyOffset();
    for (int i=firstIndex; i<mo->propertyCount(); ++i)
    {
        if (mo->property(i).isScriptable())
        {
            /* TODO
             *
             * What we really need here is:
             *   - an editor factor
             *   - combined with default values (ranges, etc) for said editor
             *   - better names for each parameter
             */
            QLabel *l = new QLabel(mo->property(i).name(), ui->propertiesDockContents);
            QWidget *editor = nullptr;
            if (QString(mo->property(i).typeName()) == "int")
            {
                QSpinBox *sb = new QSpinBox(ui->propertiesDockContents);
                sb->setRange(1, 5000);
                sb->setValue(m_fractalView->property(mo->property(i).name()).toInt());
                connect(sb, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                        [this, i](int newValue) {
                            this->m_fractalView->setProperty(this->m_fractalView->metaObject()->property(i).name(), newValue);
                        } );

                editor = sb;                
            }
            else if (QString(mo->property(i).typeName()) == "double" ||
                     QString(mo->property(i).typeName()) == "float")
            {
                QDoubleSpinBox *sb = new QDoubleSpinBox(ui->propertiesDockContents);
                sb->setRange(0.1, 100.0);
                sb->setSingleStep(0.1);
                sb->setValue(m_fractalView->property(mo->property(i).name()).toDouble());
                connect(sb, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                        [this, i](double newValue) {
                            this->m_fractalView->setProperty(this->m_fractalView->metaObject()->property(i).name(), newValue);
                        } );

                editor = sb;
            }

            // For non-editable, let's just do a static line edit
            if (editor == nullptr)
            {
                editor = new QLineEdit(m_fractalView->property(mo->property(i).name()).toString(), ui->propertiesDockContents);
                editor->setEnabled(false);
            }
            layout->addRow(l, editor);
        }
    }

    QCheckBox *autoRedraw = new QCheckBox(tr("Auto redraw"), ui->propertiesDockContents);
    autoRedraw->setChecked(m_fractalView->autoRedraw());
    QPushButton *forceRedraw = new QPushButton(tr("Redraw"), ui->propertiesDockContents);
    connect(autoRedraw, &QCheckBox::stateChanged, m_fractalView, &AbstractFractalView::setAutoRedraw);
    connect(forceRedraw, &QPushButton::clicked, m_fractalView, &AbstractFractalView::forceRedraw);
    layout->addRow(autoRedraw, forceRedraw);

    connect(ui->actionFileNew, &QAction::triggered, this, &MainWindow::onNew);
    connect(ui->actionFileExit, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(m_fractalView, &AbstractFractalView::statusBarUpdate, this, &MainWindow::onStatusBarUpdate);
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

void MainWindow::onStatusBarUpdate(const QString &text)
{
    m_statusLabel->setText(text);
}
