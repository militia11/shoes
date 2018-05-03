#ifndef EDYCJAZAMOWIENIADIALOG_H
#define EDYCJAZAMOWIENIADIALOG_H

#include <QDialog>
#include "BazaDanychManager.h"
#include "klienciDialog.h"
#include "handlowceDialog.h"
#include "modeleDialog.h"

namespace Ui {
class EdycjaZamowieniaDialog;
}

class EdycjaZamowieniaDialog : public QDialog {
    Q_OBJECT

public:
    explicit EdycjaZamowieniaDialog(klienciDialog * dialogKlienci, handlowceDialog * dialogHandl, modeleDialog * dialogmodele, BazaDanychManager *db, QWidget *parent = 0);
    ~EdycjaZamowieniaDialog();
    void setNrZam(QString nrZami);
    void setNrZamWl(QString nrZami);

private slots:
    void refreshTable();
    void updateZamSum(const QModelIndex &topLeft, const QModelIndex &bot,
                      const QVector<int> &);
    void on_pushButtonModel_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_6_clicked();

    void SelectionOfTableChanged(
        const QItemSelection &aSelected,
        const QItemSelection &aDeselected);
signals:
    void koniecEdycji();
private:
    void czysc();
    void setSumaZamowien();
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    Ui::EdycjaZamowieniaDialog *ui;
    BazaDanychManager *dbManager;
    QString nrZam;
    QString nrZamwl;
    int idKli;
    QString kliSkrot;
    klienciDialog *dialogKlienci;
    handlowceDialog *dialogHandl;
    modeleDialog *dialogmodele;
};

#endif // EDYCJAZAMOWIENIADIALOG_H
