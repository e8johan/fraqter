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
