#ifndef ROZKROJEDIALOG_H
#define ROZKROJEDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
#include <QTextDocument>
#include <QPageSetupDialog>
#include <QPrinter>
//#include <QPdfWriter>
namespace Ui {
class RozkrojeDialog;
}

class RozkrojeDialog : public QDialog {
        Q_OBJECT

    public:
        explicit RozkrojeDialog(BazaDanychManager *db, QWidget *parent = 0);
        ~RozkrojeDialog();

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

    private:
        void drukuj();
        bool pageSetup(QPrinter *printer);
        void dodajZamowieniaDoHtml(QTextDocument *document);
        void printDocument(QPrinter *printer);
        void stworzListeCaleZamowienie();
        void stworzListeZamowienSzczegoly();
        QString zamowienieTabelka(zamowienieZRozmiaramiStruct zamowienie);
        void oznaczDrukowano();
        void showEvent(QShowEvent *e);
        //  void hideEvent(QHideEvent *e);
        QVector<zamowienieZRozmiaramiStruct> zamowieniaDruk;
        QVector<int> idDrukowanychZam;
        BazaDanychManager *dbManager;
        Ui::RozkrojeDialog *ui;
        QSortFilterProxyModel *proxy;
        void deleteOldModel();
};

#endif // ROZKROJEDIALOG_H
