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
    explicit MainWindow(const QString &fractalId, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNew();

private:
    Ui::MainWindow *ui;

    AbstractFractalView *m_fractalView;
};

#endif // MAINWINDOW_H
