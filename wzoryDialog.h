#ifndef WZORYDIALOG_H
#define WZORYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
#include "nowywzorDialog.h"

namespace Ui {
class wzoryDialog;
}

class wzoryDialog : public QDialog {
    Q_OBJECT

public:
    explicit wzoryDialog(nowywzorDialog * nw,BazaDanychManager *db, QWidget *parent = 0);
    ~wzoryDialog();
    int selectExec();
    void ustawIFiltruj();
    int getAktualnyWzorNr() const;

public slots:
    virtual int exec();
private slots:
    void on_pushButton_2_clicked();
    void wybranoWzor(const QModelIndex index);

    void on_pushSzukaj_clicked();

private:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    int aktualnyWzorNr;
    Ui::wzoryDialog *ui;
    BazaDanychManager *dbManager;
    nowywzorDialog * nw;
    QSortFilterProxyModel *proxy;
    void aktualizujTabele();
};

#endif // WZORYDIALOG_H
