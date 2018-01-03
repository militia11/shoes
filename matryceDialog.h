#ifndef MATRYCEDIALOG_H
#define MATRYCEDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include "NowaMatrycaDialog.h"
#include <QSortFilterProxyModel>
namespace Ui {
class matryceDialog;
}

class matryceDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit matryceDialog(NowaMatrycaDialog *nowamat, BazaDanychManager *db,
					   QWidget *parent = 0);
		~matryceDialog();

		QString getAktualnaMatrycaNazwa() const;
		int selectExec();
	public slots:
		virtual int exec();
	private slots:
		void on_pushButton_2_clicked();
		void wybranoMatryce(const QModelIndex index);

	private:
		void showEvent(QShowEvent *e);
		QString aktualnaMatrycaNazwa;
		Ui::matryceDialog *ui;
		BazaDanychManager *dbManager;
		NowaMatrycaDialog *nowamat;
		QSortFilterProxyModel *proxy;
		bool wybieranie;
};

#endif // MATRYCEDIALOG_H
