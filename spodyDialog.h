#ifndef SPODYDIALOG_H
#define SPODYDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include "nowySpodDialog.h"
#include "clickableLabel.h"
#include "ZdjecieDialog.h"
#include <QSortFilterProxyModel>
#include <QApplication>

namespace Ui {
class spodyDialog;
}

class spodyDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit spodyDialog(ZdjecieDialog *zdj, nowySpodDialog *dialogNSpod,
					 BazaDanychManager *db,
					 QWidget *parent = 0);
		~spodyDialog();
		int selectExec();

		QString getAktualnySpodNazwa() const;

	public slots:
		virtual int exec();
	private slots:
		void wybranoSpod(const QModelIndex index);
		void zdj1();
		void zdj2();
		void zdj3();
		void zdj4();
		void on_pushButton_2_clicked();

		void on_pushButton_3_clicked();

		void on_pushButton_4_clicked();

		void on_pushButton_6_clicked();

		void on_pushButton_7_clicked();

		void on_tableView_clicked(const QModelIndex &index);

	private:
		void showEvent(QShowEvent *e);
		void hideEvent(QHideEvent *e);
		QString aktualnySpodNazwa;
		clickableLabel *label1;
		clickableLabel *label2;
		clickableLabel *label3;
		clickableLabel *label4;
		QImage image1;
		QImage image2;
		QImage image3;
		QImage image4;
		Ui::spodyDialog *ui;
		nowySpodDialog *dialogNSpod;
		ZdjecieDialog *dialogZdj;
		BazaDanychManager *dbManager;
		QSortFilterProxyModel *proxy;
		void showPhoto(QImage im);
		int getId();
                void aktualizujTabele();
};

#endif // SPODYDIALOG_H
