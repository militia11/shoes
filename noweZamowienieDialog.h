#ifndef NOWEZAMOWIENIEDIALOG_H
#define NOWEZAMOWIENIEDIALOG_H

#include <QtWidgets/QDialog>

#include "WybKlientaDialog.h"
#include "WybHandlDialog.h"
#include "nowyKlientDialog.h"
#include "BazaDanychManager.h"
#include "WybModelDialog.h"
#include "NowyHandlowiecDialog.h"
#include <QStandardItemModel>
namespace Ui {
class noweZamowienieDialog;
}

class noweZamowienieDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit noweZamowienieDialog(NowyHandlowiecDialog *nh,
						  WybHandlDialog *wybHandlDialog,
						  BazaDanychManager *db, WybModelDialog *modeleDialog, WybKlientaDialog *dialog,
						  nowyKlientDialog *nowyKliDialog, QWidget *parent = 0);
		~noweZamowienieDialog();

	private slots:
		void obliczSume(QStandardItem *it);
		void on_pushButton_5_clicked();
		void on_pushButton_6_clicked();

		void on_buttonBox_accepted();
		void on_buttonBox_rejected();
		void on_pushButton_9_clicked();
		void on_pushButtonModel_clicked();
		void on_pushButton_7_clicked();

		void on_checkBox_stateChanged(int arg1);

	private:
		void keyPressEvent(QKeyEvent *event);
		void showEvent(QShowEvent *e);
		void wyczysc();

		BazaDanychManager *dbManager;
		int idZamowienia;
		WybModelDialog *modeleDialog;
		WybKlientaDialog *dialog;
		WybHandlDialog *dialogHandl;
		nowyKlientDialog *nowyKliDialog;
		NowyHandlowiecDialog *nowyHandlDialog;
		Ui::noweZamowienieDialog *ui;
		QStandardItemModel *zamowienie;
		int ktoraPozycja;
		void ustawTabeleHeaders();
};

#endif // NOWEZAMOWIENIEDIALOG_H
