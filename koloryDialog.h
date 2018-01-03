#ifndef KOLORYDIALOG_H
#define KOLORYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
namespace Ui {
class koloryDialog;
}

class koloryDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit koloryDialog(BazaDanychManager *db, QWidget *parent = 0);
		~koloryDialog();

	private slots:
		void on_pushButton_2_clicked();

	private:
		void showEvent(QShowEvent *e);
		Ui::koloryDialog *ui;
		BazaDanychManager *dbManager;
		QSortFilterProxyModel *proxy;
};

#endif // KOLORYDIALOG_H
