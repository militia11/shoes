#ifndef NOWEZAMOWIENIEDIALOG_H
#define NOWEZAMOWIENIEDIALOG_H

#include <QtWidgets/QDialog>

#include "klienciDialog.h"
#include "nowyKlientDialog.h"
#include "owyModelDialog.h"
#include "BazaDanychManager.h"
#include "modeleDialog.h"
#include "NowyHandlowiecDialog.h"
#include "handlowceDialog.h"
#include "mwdialog.h"
#include <QStandardItemModel>
#include "DelegateArrows.h"
namespace Ui {
class noweZamowienieDialog;
}

class noweZamowienieDialog : public QDialog {
    Q_OBJECT

public:
    noweZamowienieDialog(mwDialog *roz,
                         handlowceDialog *wybHandlDialog,
                         BazaDanychManager *db, modeleDialog *modeleDialog, klienciDialog *dialog,
                         QWidget *parent = 0);
    ~noweZamowienieDialog();

    void setNr(const QString &value);

    void sumall();

private slots:
    void obliczSume(QStandardItem *it);
    void on_pushButton_5_clicked();

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_checkBox_stateChanged(int arg1);
    void on_tableViewZam_clicked(const QModelIndex &index);

    void on_plainTextEditU1_textChanged();

    void SelectionOfTableChanged(
        const QItemSelection &aSelected,
        const QItemSelection &aDeselected);
    void ShowContextMenu(const QPoint &pos);

    void on_pushButtonModel_2_clicked();


public slots:
    void  abra(QWidget*);

private:
    bool eventFilter(QObject *object, QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *e);
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    void wyczysc();
void anuluj();
    std::list<int> pojemnikIdMW;
    QMap<int, int> pojemnikRzad;
    QStringList uwagi;
    mwDialog *roz;
    BazaDanychManager *dbManager;
    int idZamowienia;
    modeleDialog *modelDialog;
    klienciDialog *dialog;
    handlowceDialog *dialogHandl;
    Ui::noweZamowienieDialog *ui;
    QStandardItemModel *zamowienie;
    int ktoraPozycja;
    QString nr;
    DelegateArrows *delArrow;
    void ustawTabeleHeaders();
    void setPlainTextEnabled(bool aEnable);
};

#endif // NOWEZAMOWIENIEDIALOG_H
