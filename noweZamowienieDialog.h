#ifndef NOWEZAMOWIENIEDIALOG_H
#define NOWEZAMOWIENIEDIALOG_H

#include <QtWidgets/QDialog>

#include "klienciDialog.h"
#include "nowyKlientDialog.h"
#include "NowyModelDialog.h"
#include "BazaDanychManager.h"
#include "modeleDialog.h"
#include "NowyHandlowiecDialog.h"
#include "handlowceDialog.h"
#include <QStandardItemModel>
namespace Ui {
class noweZamowienieDialog;
}

class noweZamowienieDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit noweZamowienieDialog(

			handlowceDialog *wybHandlDialog,
			BazaDanychManager *db, modeleDialog *modeleDialog, klienciDialog *dialog,
			QWidget *parent = 0);
		~noweZamowienieDialog();

	private slots:
		void obliczSume(QStandardItem *it);
		void on_pushButton_5_clicked();

		void on_buttonBox_accepted();
		void on_buttonBox_rejected();
		void on_pushButton_9_clicked();
		void on_pushButtonModel_clicked();

		void on_checkBox_stateChanged(int arg1);

		void on_pushButton_10_clicked();

		void on_tableViewZam_clicked(const QModelIndex &index);

		void on_plainTextEditU1_textChanged();

		void SelectionOfTableChanged(
			const QItemSelection &aSelected,
			const QItemSelection &aDeselected);
	private:
		void keyPressEvent(QKeyEvent *event);
		void showEvent(QShowEvent *e);
		void wyczysc();

		QStringList uwagi;
		BazaDanychManager *dbManager;
		int idZamowienia;
		modeleDialog *modelDialog;
		klienciDialog *dialog;
		handlowceDialog *dialogHandl;
		Ui::noweZamowienieDialog *ui;
		QStandardItemModel *zamowienie;
		int ktoraPozycja;
		QString nr;
		void ustawTabeleHeaders();
		void setPlainTextEnabled(bool aEnable);
};

#endif // NOWEZAMOWIENIEDIALOG_H
