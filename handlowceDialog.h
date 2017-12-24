#ifndef HANDLOWCEDIALOG_H
#define HANDLOWCEDIALOG_H
#include "BazaDanychManager.h"
#include "NowyHandlowiecDialog.h"
#include <QtWidgets/QDialog>
#include <QSortFilterProxyModel>

namespace Ui {
class handlowceDialog;
}

class handlowceDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit handlowceDialog(NowyHandlowiecDialog *nowyKliDialog,
					 BazaDanychManager *db, QWidget *parent = 0);
		~handlowceDialog();

	private slots:
		void on_pushButton_3_clicked();

	private:
		void showEvent(QShowEvent *e);
		Ui::handlowceDialog *ui;
		BazaDanychManager *dbManager;
		NowyHandlowiecDialog *nowyKliDialog;
		QSortFilterProxyModel *proxy;
};

#endif // HANDLOWCEDIALOG_H
