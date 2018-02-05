#ifndef SKORYDIALOG_H
#define SKORYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include "nowaSkoraDialog.h"
#include <QSortFilterProxyModel>

namespace Ui {
class skoryDialog;
}

class skoryDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit skoryDialog(nowaSkoraDialog *ns, BazaDanychManager *db,
					 QWidget *parent = 0);
		~skoryDialog();
		int selectExec();
		QString getAktualnaSkoraNazwa() const;

	public slots:
		virtual int exec();
		void wybranoSkore(const QModelIndex index);
	private slots:
		void updateZamSum(const QModelIndex &, const QModelIndex &, const QVector<int> &);
		void on_pushButton_2_clicked();

		void on_tableViewKlienci_clicked(const QModelIndex &index);

		void on_buttonBox_accepted();

		void on_buttonBox_rejected();

	private:
		void showEvent(QShowEvent *e);
		void hideEvent(QHideEvent *e);
		Ui::skoryDialog *ui;
		BazaDanychManager *dbManager;
		nowaSkoraDialog *ns;
		QSortFilterProxyModel *proxy;
		QString aktualnaSkoraNazwa;
		QSqlQueryModel *m ;
		void getceny();
	};

#endif // SKORYDIALOG_H
