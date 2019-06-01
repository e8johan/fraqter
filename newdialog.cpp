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
