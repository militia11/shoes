#ifndef SPODYDIALOG_H
#define SPODYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include "nowySpodDialogx.h"
namespace Ui {
class spodyDialog;
}

class spodyDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit spodyDialog(nowySpodDialog *dialogNSpod, BazaDanychManager *db,
					 QWidget *parent = 0);
		~spodyDialog();

	private slots:
		void on_pushButton_2_clicked();

	private:
		void showEvent(QShowEvent *e);
		Ui::spodyDialog *ui;
		BazaDanychManager *dbManager;
		nowySpodDialog *dialogNSpod;
};

#endif // SPODYDIALOG_H
