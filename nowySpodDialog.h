#ifndef NOWYSPODDIALOG_H
#define NOWYSPODDIALOG_H

#include <QtWidgets/QDialog>
#include "ManagerZdjec.h"
#include <QKeyEvent>
namespace Ui {
class nowySpodDialog;
}

class nowySpodDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit nowySpodDialog(QWidget *parent = 0);
		~nowySpodDialog();

		QString getNazwa() const;

		QString getProducent() const;

		QString getRodzaj() const;

		QString getUwagi() const;

		QString getRozm() const;

		int getIloscZdj() const;

		QVector<QImage> getImages() const;

	private slots:
		void on_pushButton_14_clicked();

		void on_pushButton_15_clicked();

		void on_pushButton_16_clicked();

		void on_pushButton_17_clicked();

		void on_buttonBox_accepted();

		void on_buttonBox_rejected();
	protected:
		void showEvent(QShowEvent *e);
		void keyPressEvent(QKeyEvent *event) {
			if (event->key() == Qt::Key_Escape) {
				wyczyscPola();
				resetujPrzyciskiWymagane();
			}
			QDialog::keyPressEvent(event);
		}
		void wyczyscPola();
		void resetujPrzyciskiWymagane();

	private:
		QString nazwa;
		QString producent;
		QString rodzaj;
		QString uwagi;
		QString rozm;

		QVector<QImage>images;
		Ui::nowySpodDialog *ui;
};

#endif // NOWYSPODDIALOG_H
