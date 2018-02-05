#ifndef KLIENCIDIALOG_H
#define KLIENCIDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include "nowyKlientDialog.h"
#include <QSortFilterProxyModel>

namespace Ui {
class klienciDialog;
}

class klienciDialog : public QDialog
{
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

	private slots:
		void wybranoKli(const QModelIndex index);
		void on_pushButton_2_clicked();
		void on_pushSzukaj_clicked();
		void on_pushButton_clicked();

	private:
		void showEvent(QShowEvent *e);
		void hideEvent(QHideEvent *e);
		QString aktualnyKlientNazwa;
		Ui::klienciDialog *ui;
		BazaDanychManager *dbManager;
		nowyKlientDialog *nowyKliDialog;
		QSortFilterProxyModel *proxy;
		void aktualizujTabele();
};

#endif // KLIENCIDIALOG_H
