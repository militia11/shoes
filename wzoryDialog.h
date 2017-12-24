#ifndef WZORYDIALOG_H
#define WZORYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
namespace Ui {
class wzoryDialog;
}

class wzoryDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit wzoryDialog(BazaDanychManager *db,QWidget *parent = 0);
		~wzoryDialog();

	private:
		void showEvent(QShowEvent *e);
		Ui::wzoryDialog *ui;BazaDanychManager *dbManager;
};

#endif // WZORYDIALOG_H
