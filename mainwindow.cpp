#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "abstractfractalview.h"
#include "abstractimaginaryrangeview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_fractalView = new AbstractImaginaryRangeView(this);
    setCentralWidget(m_fractalView);

    connect(ui->actionFileExit, &QAction::triggered, qApp, &QCoreApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
