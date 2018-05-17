#ifndef MWDIALOG_H
#define MWDIALOG_H

#include <QDialog>
#include "BazaDanychManager.h"
#include "rozmiaryDialog.h"
#include "owyModelDialog.h"
#include <QSortFilterProxyModel>
namespace Ui {
class mwDialog;
}

class mwDialog : public QDialog {
    Q_OBJECT
public:
    int selectExec();
    explicit mwDialog(owyModelDialog* nm,  rozmiaryDialog *roz, BazaDanychManager *db, QWidget *parent = 0);
    ~mwDialog();
    virtual int exec();
    void ustawIFiltruj();
    QList<QStandardItem *> zwrocWierszModel();
    int getActualLastId() const;

    bool getZmagazynu() const;

    void czysc();

private slots:

    void SelectionOfTableChanged(
        const QItemSelection &aSelected,
        const QItemSelection &aDeselected);
    void on_pushButtonZw_clicked();

    void on_pushButtonPu_clicked();

    void on_pushButtonSzukaj_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    bool zmagazynu;
    int actualLastId;
    void showEvent(QShowEvent *e);
    owyModelDialog *nm;
    BazaDanychManager *dbManager;
    rozmiaryDialog *roz;
    Ui::mwDialog *ui;
    QSortFilterProxyModel *proxy;
};

#endif // MWDIALOG_H
