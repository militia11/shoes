#ifndef HISTORIADRUKDIALOG_H
#define HISTORIADRUKDIALOG_H

#include <QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>

namespace Ui {
class historiaDrukDialog;
}

class historiaDrukDialog : public QDialog
{
    Q_OBJECT

public:
    explicit historiaDrukDialog(BazaDanychManager *dbManager, QWidget *parent = 0);
    ~historiaDrukDialog();

private slots:
    void showEvent(QShowEvent *e);

    void on_pushButtonSzukaj_clicked();

    void on_pushButton_clicked();

private:
    void czysc();
    void ustawIFiltruj();
    BazaDanychManager *dbManager;
    Ui::historiaDrukDialog *ui;  QSortFilterProxyModel *proxy;
};

#endif // HISTORIADRUKDIALOG_H
