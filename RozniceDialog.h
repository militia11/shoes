#ifndef ROZNICEDIALOG_H
#define ROZNICEDIALOG_H
#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>

namespace Ui {
class RozniceDialog;
}

class RozniceDialog : public QDialog {
        Q_OBJECT

    public:
        explicit RozniceDialog(BazaDanychManager *db, QWidget *parent = 0);
        ~RozniceDialog();
    void setWskazRoznice(bool value);

    void setNrRoznicy(const QString &value);

private slots:
    void on_tableView_clicked(const QModelIndex &index);
        void SelectionOfTableChanged(
            const QItemSelection &aSelected,
            const QItemSelection &aDeselected);

        void on_pushSzukaj_clicked();

private:
        void ustawIFiltruj();
         void czysc();
        void showEvent(QShowEvent *e);
        void hideEvent(QHideEvent *e);
        BazaDanychManager *dbManager;
        Ui::RozniceDialog *ui;
        QSortFilterProxyModel *proxy;
        void deleteOldModel();
        bool wskazRoznice;
        QString nrRoznicy;
};

#endif // ROZNICEDIALOG_H
