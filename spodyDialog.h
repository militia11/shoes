#ifndef SPODYDIALOG_H
#define SPODYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
namespace Ui {
class spodyDialog;
}

class spodyDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit spodyDialog(BazaDanychManager *db,QWidget *parent = 0);
		~spodyDialog();

	private:
		void showEvent(QShowEvent *e);
		Ui::spodyDialog *ui;BazaDanychManager *dbManager;
};

#endif // SPODYDIALOG_H
