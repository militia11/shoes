#ifndef WYBKLIENTADIALOG_H
#define WYBKLIENTADIALOG_H
#include "BazaDanychManager.h"
#include <QtWidgets/QDialog>

namespace Ui {
class WybKlientaDialog;
}

class WybKlientaDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit WybKlientaDialog(BazaDanychManager *db, QWidget *parent = 0);
		~WybKlientaDialog();

		void setTable();

	private:
		void showEvent(QShowEvent *e);

	private:
		BazaDanychManager *db;
		Ui::WybKlientaDialog *ui;
};

#endif // WYBKLIENTADIALOG_H
