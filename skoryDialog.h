#ifndef SKORYDIALOG_H
#define SKORYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
namespace Ui {
class skoryDialog;
}

class skoryDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit skoryDialog(BazaDanychManager *db,QWidget *parent = 0);
		~skoryDialog();

	private:
		void showEvent(QShowEvent *e);
		Ui::skoryDialog *ui;	BazaDanychManager *dbManager;
};

#endif // SKORYDIALOG_H
