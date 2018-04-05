#ifndef PZDIALOG_H
#define PZDIALOG_H
#include "BazaDanychManager.h"
#include <QDialog>
#include <QSortFilterProxyModel>
#include "rozmiaryDialog.h"
namespace Ui {
class pzDialog;
}

class pzDialog : public QDialog {
    Q_OBJECT

public:
    explicit pzDialog(rozmiaryDialog *roz, BazaDanychManager *db,QWidget *parent = 0);
    ~pzDialog();

    void ustawIFiltruj();
    int getActualLastId() const;
    void czysc();

private slots:
    void on_pushButtonSzukaj_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

private:
    int actualLastId;
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);

    BazaDanychManager *dbManager;
    rozmiaryDialog *roz;
    QSortFilterProxyModel *proxy;
    Ui::pzDialog *ui;
};

#endif // PZDIALOG_H
