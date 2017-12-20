#ifndef WYBMODELDIALOG_H
#define WYBMODELDIALOG_H

#include <QtWidgets/QDialog>

#include "BazaDanychManager.h"

namespace Ui {
class WybModelDialog;
}

class WybModelDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit WybModelDialog(BazaDanychManager *db, QWidget *parent = 0);
		~WybModelDialog();
		void aktualizujTabele();
	private slots:
		void akceptujModel(const QModelIndex index);

	private:
		void showEvent(QShowEvent *e);
		BazaDanychManager *dbManager;
		Ui::WybModelDialog *ui;
	};

#endif // WYBMODELDIALOG_H
