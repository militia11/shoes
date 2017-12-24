#ifndef WYBHANDLDIALOG_H
#define WYBHANDLDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
namespace Ui {
class WybHandlDialog;
}

class WybHandlDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit WybHandlDialog(BazaDanychManager *db, QWidget *parent = 0);
		~WybHandlDialog();

		void aktualizujTabele();
		QString getAktualnyHandlNazwa();

	private slots:
		void akceptujHandl(const QModelIndex index);

		void on_pushButton_clicked();

	private:
		void showEvent(QShowEvent *e);

		QString aktualnyHandlNazwa;
		BazaDanychManager *dbManager;
		Ui::WybHandlDialog *ui;
		QSortFilterProxyModel *proxy;
};

#endif // WYBHANDLDIALOG_H
