#ifndef RWDIALOG_H
#define RWDIALOG_H

#include <QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
namespace Ui {
class rwDialog;
}

class rwDialog : public QDialog {
    Q_OBJECT

public:
    explicit rwDialog( BazaDanychManager *db,QWidget *parent = 0);
    ~rwDialog();
    void ustawIFiltruj();
private slots:
    void on_pushButtonSzukaj_clicked();

    void on_pushButton_clicked();

private:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    Ui::rwDialog *ui;
    BazaDanychManager *dbManager;
    QSortFilterProxyModel *proxy;
};

#endif // RWDIALOG_H
