#ifndef OCIEPLENIEDIALOG_H
#define OCIEPLENIEDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
namespace Ui {
class ocieplenieDialog;
}

class ocieplenieDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit ocieplenieDialog(BazaDanychManager *db, QWidget *parent = 0);
		~ocieplenieDialog();

	private:
		void showEvent(QShowEvent *e);
		Ui::ocieplenieDialog *ui;
		BazaDanychManager *dbManager;
};

#endif // OCIEPLENIEDIALOG_H
