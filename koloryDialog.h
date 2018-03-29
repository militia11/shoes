#ifndef KOLORYDIALOG_H
#define KOLORYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
#include "nowyKolorDialog.h"

namespace Ui {
class koloryDialog;
}

class koloryDialog : public QDialog {
    Q_OBJECT

public:
    explicit koloryDialog(nowyKolorDialog *dilogNowyKolor, BazaDanychManager *db,
                          QWidget *parent = 0);
    ~koloryDialog();
    void ustawIFiltruj();
    int getAktualnyKolor() const;
    int selectExec();

private slots:
    void on_pushButton_2_clicked();
    void wybranoKolor(const QModelIndex index);
    void on_pushSzukaj_clicked();

    void on_pushButton_clicked();

public slots:
    virtual int exec();

protected:
    void aktualHeader();

private:
    int aktualnyKolor;
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    Ui::koloryDialog *ui;
    BazaDanychManager *dbManager;
    QSortFilterProxyModel *proxy;
    nowyKolorDialog *nowyKolor;
    void czysc();
};

#endif // KOLORYDIALOG_H
