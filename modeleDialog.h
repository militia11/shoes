#ifndef MODELEDIALOG_H
#define MODELEDIALOG_H

#include <QtWidgets/QDialog>
#include "BazaDanychManager.h"
#include "owyModelDialog.h"

#include <QSortFilterProxyModel>
#include "clickableLabel.h"

namespace Ui {
class modeleDialog;
}
struct modelRodzaje
{
	QString typ;
	QString mont;
	QString r1;
	QString r2;
	QString r3;
	QString r4;
	QString r5;
	QString r6;
};
class modeleDialog : public QDialog {
		Q_OBJECT

	public:
        explicit modeleDialog( ZdjecieDialog *zdj, owyModelDialog *nowyModDialog,
					   BazaDanychManager *db,
					   QWidget *parent = 0);
		~modeleDialog();
		int selectExec();
		void ustawIFiltruj();
	public slots:
		virtual int exec();
		void wybranoModel(const QModelIndex index);

	private slots:
		void zdj1();
		void zdj2();
		void zdj3();
		void zdj4();
		void on_pushButton_2_clicked();
		void on_pushButton_3_clicked();
		void on_tableView_clicked(const QModelIndex &index);
		void on_pushButtonSzukaj_clicked();
		void on_pushButton_clicked();

		void on_comboBoxtyp_activated(int index);
		void on_comboBoxmont_activated(int index);
		void on_comboBoxb1_activated(int index);
		void on_comboBoxb2_activated(int index);
		void on_comboBoxb3_activated(int index);
		void on_comboBoxb4_activated(int index);
		void on_comboBoxb5_activated(int index);
		void on_comboBoxb6_activated(int index);

	private:
		void wyczyscPola();
		void showPhoto(QImage im);
		void showEvent(QShowEvent *e);
		void hideEvent(QHideEvent *e);
		clickableLabel *label1;
		clickableLabel *label2;
		clickableLabel *label3;
		clickableLabel *label4;
		Ui::modeleDialog *ui;
		QImage image1;
		QImage image2;
		QImage image3;
		QImage image4;
		BazaDanychManager *dbManager;
        owyModelDialog *nowyModDialog;
		ZdjecieDialog *dialogZdj;
		QSortFilterProxyModel *proxy;
		modelRodzaje filtrRodzaje;
		int getId();
		void ustawCombo(QString tabela, QComboBox *com);
		void createCombos();
		void resetRodzaje();
};

#endif // MODELEDIALOG_H
