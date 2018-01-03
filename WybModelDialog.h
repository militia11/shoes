#ifndef WYBMODELDIALOG_H
#define WYBMODELDIALOG_H

#include <QtWidgets/QDialog>

#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
namespace Ui {
class WybModelDialog;
}

class WybModelDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit WybModelDialog(BazaDanychManager *db, QWidget *parent = 0);
		~WybModelDialog();
		void aktualizujTabele();
	private slots:
		void akceptujModel(const QModelIndex index);

	private:
		void showEvent(QShowEvent *e);
		BazaDanychManager *dbManager;
		Ui::WybModelDialog *ui;
		QSortFilterProxyModel *proxy;
};

#endif // WYBMODELDIALOG_H
