#ifndef WZORYDIALOG_H
#define WZORYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
namespace Ui {
class wzoryDialog;
}

class wzoryDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit wzoryDialog(BazaDanychManager *db, QWidget *parent = 0);
		~wzoryDialog();

	private slots:
		void on_pushButton_2_clicked();

	private:
		void showEvent(QShowEvent *e);
		Ui::wzoryDialog *ui;
		BazaDanychManager *dbManager;
		QSortFilterProxyModel *proxy;
};

#endif // WZORYDIALOG_H
