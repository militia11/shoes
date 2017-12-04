#ifndef NOWEZAMOWIENIEDIALOG_H
#define NOWEZAMOWIENIEDIALOG_H

#include <QtWidgets/QDialog>

#include "WybKlientaDialog.h"

namespace Ui {
class noweZamowienieDialog;
}

class noweZamowienieDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit noweZamowienieDialog(WybKlientaDialog *dialog, QWidget *parent = 0);
		~noweZamowienieDialog();

	private slots:
		void on_pushButton_3_clicked();

		void on_pushButton_clicked();

	private:
		WybKlientaDialog *dialog;
		Ui::noweZamowienieDialog *ui;
};

#endif // NOWEZAMOWIENIEDIALOG_H
