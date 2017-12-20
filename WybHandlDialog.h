#ifndef WYBHANDLDIALOG_H
#define WYBHANDLDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"

namespace Ui {
class WybHandlDialog;
}

class WybHandlDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit WybHandlDialog(BazaDanychManager *db,QWidget *parent = 0);
		~WybHandlDialog();

		void aktualizujTabele();
		QString getAktualnyHandlNazwa();

	private slots:
		void akceptujHandl(const QModelIndex index);

	private:
		void showEvent(QShowEvent *e);

		QString aktualnyHandlNazwa;
		BazaDanychManager *dbManager;
		Ui::WybHandlDialog *ui;
	};

#endif // WYBHANDLDIALOG_H
