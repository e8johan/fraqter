#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AbstractFractalView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    AbstractFractalView *m_fractalView;
};

#endif // MAINWINDOW_H
