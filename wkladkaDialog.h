#ifndef WKLADKADIALOG_H
#define WKLADKADIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
#include "nowawkladkadialog.h"
namespace Ui {
class wkladkaDialog;
}

class wkladkaDialog : public QDialog
{
		Q_OBJECT

	public:
        explicit wkladkaDialog(NowaWkladkaDialog *dialogNowaWkl, BazaDanychManager *db, QWidget *parent = 0);
		~wkladkaDialog();
		int selectExec();

		QString getAktualnaWkladkaNazwa() const;

	public slots:
		virtual int exec();
		void wybranoWkl(const QModelIndex index);

	private slots:
		void on_pushButton_2_clicked();

	private:
		void showEvent(QShowEvent *e);
		void hideEvent(QHideEvent *e);
		QString aktualnaWkladkaNazwa;
        NowaWkladkaDialog *dialogNowaWkl;
		BazaDanychManager *dbManager;
		Ui::wkladkaDialog *ui;
		QSortFilterProxyModel *proxy;
		void aktualizujTabele();
};

#endif // WKLADKADIALOG_H
