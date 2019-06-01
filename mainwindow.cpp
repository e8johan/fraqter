#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fractalmandelbrot.h"
#include "fractaljulia.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    m_fractalView = new FractalMandelbrot(this);
    m_fractalView = new FractalJulia(this);
    setCentralWidget(m_fractalView);

    connect(ui->actionFileExit, &QAction::triggered, qApp, &QCoreApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
