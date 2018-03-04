#ifndef ROZKROJEDIALOG_H_
#define ROZKROJEDIALOG_H_

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
#include <QTextDocument>
#include <QPrinter>
#include <QPageSetupDialog>

namespace Ui {
class RozkrojeDialog;
}

class RozkrojeDialog : public QDialog {
        Q_OBJECT

    public:
        explicit RozkrojeDialog(BazaDanychManager *db, QWidget *parent = 0);
        ~RozkrojeDialog();

        void setDodanoRozkroj(bool value);
        void setWskazRozkroj(bool value);

        void setNrRozkrojuWskaz(const QString &value);

private slots:
        void on_tableView_clicked(const QModelIndex &index);

        void on_pushButtonPrint_clicked();
        void SelectionOfTableChanged(
            const QItemSelection &aSelected,
            const QItemSelection &aDeselected);
        void SelectionOfTableChangedSzczegoly(
            const QItemSelection &aSelected,
            const QItemSelection &aDeselected);
        void on_pushButtonPrint_2_clicked();

        void on_pushSzukaj_clicked();

private:
        void ustawIFiltruj();
        void czysc();
        void drukuj();
        bool pageSetup(QPrinter *printer);
        void dodajZamowieniaDoHtml(QTextDocument *document);
        void printDocument(QPrinter *printer);
        void stworzListeCaleZamowienie();
        void stworzListeZamowienSzczegoly();
        QString zamowienieTabelka(zamowienieZRozmiaramiStruct zamowienie);
        QString nrRozkrojuWskaz;
        void oznaczDrukowano();
        void showEvent(QShowEvent *e);
        void hideEvent(QHideEvent *e);
        QVector<zamowienieZRozmiaramiStruct> zamowieniaDruk;
        QVector<int> idDrukowanychZam;
        BazaDanychManager *dbManager;
        Ui::RozkrojeDialog *ui;
        QSortFilterProxyModel *proxy;
        void deleteOldModel();
        bool dodanoRozkroj;
        bool wskazRozkroj;
        QSqlQueryModel *vModel;
        void wyczyscListy();
        zamowienieZRozmiaramiStruct prepareZamowienieDruk(int i);
};

#endif // ROZKROJEDIALOG_H_
