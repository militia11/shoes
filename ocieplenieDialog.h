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

		QString getAktualnyKolor() const;

		int selectExec();
	private slots:

		void on_pushButton_2_clicked();
		void wybranoOc(const QModelIndex index);
	public slots:
		virtual int exec();

	private:
		void showEvent(QShowEvent *e);
		void hideEvent(QHideEvent *e);
		QString aktualnyKolor;
		Ui::ocieplenieDialog *ui;
		BazaDanychManager *dbManager;
		QSortFilterProxyModel *proxy;
};

#endif // OCIEPLENIEDIALOG_H
