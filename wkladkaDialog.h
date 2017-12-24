#ifndef WKLADKADIALOG_H
#define WKLADKADIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
namespace Ui {
class wkladkaDialog;
}

class wkladkaDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit wkladkaDialog(BazaDanychManager *db,QWidget *parent = 0);
		~wkladkaDialog();

	private:
		void showEvent(QShowEvent *e);
		BazaDanychManager *dbManager;
		Ui::wkladkaDialog *ui;
};

#endif // WKLADKADIALOG_H
