#ifndef OCIEPLENIEDIALOG_H
#define OCIEPLENIEDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include <QSortFilterProxyModel>
#include "noweociepdialog.h"
namespace Ui {
class ocieplenieDialog;
}

class ocieplenieDialog : public QDialog
{
		Q_OBJECT

	public:
        explicit ocieplenieDialog(noweociepdialog *dno, BazaDanychManager *db, QWidget *parent = 0);
		~ocieplenieDialog();

		QString getAktualnyKolor() const;

		int selectExec();
                void aktualizujTabele();
                
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
        noweociepdialog *dno;
		BazaDanychManager *dbManager;
		QSortFilterProxyModel *proxy;
};

#endif // OCIEPLENIEDIALOG_H
