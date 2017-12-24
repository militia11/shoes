#ifndef KLIENCIDIALOG_H
#define KLIENCIDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include "nowyKlientDialog.h"
#include <QSortFilterProxyModel>

namespace Ui {
class klienciDialog;
}

class klienciDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit klienciDialog(nowyKlientDialog *nowyKliDialog, BazaDanychManager *db,
					   QWidget *parent = 0);
		~klienciDialog();

	private slots:
		void on_pushButton_2_clicked();

	private:
		void showEvent(QShowEvent *e);

		Ui::klienciDialog *ui;
		BazaDanychManager *dbManager;
		nowyKlientDialog *nowyKliDialog;
		QSortFilterProxyModel *proxy;
};

#endif // KLIENCIDIALOG_H
