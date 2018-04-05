#ifndef KLIENCIDIALOG_H
#define KLIENCIDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include "nowyKlientDialog.h"
#include <QSortFilterProxyModel>
#include "delegateKli.h"

namespace Ui {
class klienciDialog;
}

class klienciDialog : public QDialog {
    Q_OBJECT

public:
    explicit klienciDialog(nowyKlientDialog *nowyKliDialog, BazaDanychManager *db,
                           QWidget *parent = 0);
    ~klienciDialog();
    QString getAktualnyKlientNazwa() const;

    void ustawIFiltruj();
    int selectExec();

public slots:
    virtual int exec();
    void abra(QWidget*, QAbstractItemDelegate::EndEditHint);

private slots:
    void wybranoKli(const QModelIndex index);
    void on_pushButton_2_clicked();
    void on_pushSzukaj_clicked();
    void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    void combo();
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    QString aktualnyKlientNazwa;
    Ui::klienciDialog *ui;
    BazaDanychManager *dbManager;
    nowyKlientDialog *nowyKliDialog;
    QSortFilterProxyModel *proxy;
    Delegate *myDelegate;
    void aktualizujTabele();
    void aktualizujHeader();
};

#endif // KLIENCIDIALOG_H
