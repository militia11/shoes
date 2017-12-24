#ifndef KOLORYDIALOG_H
#define KOLORYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
namespace Ui {
class koloryDialog;
}

class koloryDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit koloryDialog(BazaDanychManager *db,QWidget *parent = 0);
		~koloryDialog();

	private:
		void showEvent(QShowEvent *e);
		Ui::koloryDialog *ui;
		BazaDanychManager *dbManager;
};

#endif // KOLORYDIALOG_H
