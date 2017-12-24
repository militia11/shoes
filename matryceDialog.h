#ifndef MATRYCEDIALOG_H
#define MATRYCEDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
namespace Ui {
class matryceDialog;
}

class matryceDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit matryceDialog(BazaDanychManager *db,QWidget *parent = 0);
		~matryceDialog();

	private:
		void showEvent(QShowEvent *e);
		Ui::matryceDialog *ui;	BazaDanychManager *dbManager;
};

#endif // MATRYCEDIALOG_H
