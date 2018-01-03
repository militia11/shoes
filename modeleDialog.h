#ifndef MODELEDIALOG_H
#define MODELEDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include "NowyModelDialog.h"
#include <QSortFilterProxyModel>
#include "clickableLabel.h"

namespace Ui {
class modeleDialog;
}

class modeleDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit modeleDialog(NowyModelDialog *nowyModDialog, BazaDanychManager *db,
					  QWidget *parent = 0);
		~modeleDialog();

	private slots:
		void on_pushButton_2_clicked();

	private:
		void showEvent(QShowEvent *e);
		Ui::modeleDialog *ui;
		BazaDanychManager *dbManager;
		NowyModelDialog *nowyModDialog;
		QSortFilterProxyModel *proxy;
};

#endif // MODELEDIALOG_H
