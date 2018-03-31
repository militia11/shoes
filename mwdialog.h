#ifndef MWDIALOG_H
#define MWDIALOG_H

#include <QDialog>
#include "BazaDanychManager.h"
#include "rozmiaryDialog.h"
#include <QSortFilterProxyModel>
namespace Ui {
class mwDialog;
}

class mwDialog : public QDialog {
    Q_OBJECT
public:
    int selectExec();
    explicit mwDialog(rozmiaryDialog *roz, BazaDanychManager *db, QWidget *parent = 0);
    ~mwDialog();
    virtual int exec();
    void ustawIFiltruj();

private slots:

    void on_pushButtonZw_clicked();

    void on_pushButtonPu_clicked();

    void on_pushButtonSzukaj_clicked();

    void on_pushButton_clicked();

private:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    BazaDanychManager *dbManager;
    rozmiaryDialog *roz;
    Ui::mwDialog *ui;
    QSortFilterProxyModel *proxy;
};

#endif // MWDIALOG_H
