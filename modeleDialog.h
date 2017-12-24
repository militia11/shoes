#ifndef MODELEDIALOG_H
#define MODELEDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include "nowyModelDialog.h"
namespace Ui {
class modeleDialog;
}

class modeleDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit modeleDialog(nowyModelDialog *nowyKliDialog,BazaDanychManager *db,QWidget *parent = 0);
		~modeleDialog();

	private slots:
		void on_pushButton_2_clicked();

	private:
		void showEvent(QShowEvent *e);
		Ui::modeleDialog *ui;
		BazaDanychManager *dbManager;
		nowyModelDialog *nowyKliDialog;
};

#endif // MODELEDIALOG_H
