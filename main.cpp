#include <QApplication>

#include "newdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NewDialog newDialog;
    if (newDialog.exec() == QDialog::Accepted)
        return a.exec();
    else
        return 0;
}
