#ifndef WYBKLIENTADIALOG_H
#define WYBKLIENTADIALOG_H

#include <QtWidgets/QDialog>

#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>

namespace Ui {
class WybKlientaDialog;
}

class WybKlientaDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit WybKlientaDialog(BazaDanychManager *db, QWidget *parent = 0);
		~WybKlientaDialog();

		void aktualizujTabele();
		QString getAktualnyKlientNazwa() const;

	private slots:
		void akceptujKlienta(const QModelIndex index);

		void on_pushSzukaj_clicked();
		void on_pushButton_clicked();

	private:
		void showEvent(QShowEvent *e);
		QString aktualnyKlientNazwa;
		BazaDanychManager *dbManager;
		Ui::WybKlientaDialog *ui;
		QSortFilterProxyModel *proxy;
};

#endif // WYBKLIENTADIALOG_H
