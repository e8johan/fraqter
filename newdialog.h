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
    QStringListModel m_fractalNames;
};

#endif // NEWDIALOG_H
