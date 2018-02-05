#ifndef NOWASKORADIALOG_H
#define NOWASKORADIALOG_H

#include <QtWidgets/QDialog>
#include<QKeyEvent>

namespace Ui {
class nowaSkoraDialog;
}

class nowaSkoraDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit nowaSkoraDialog(QWidget *parent = 0);
		~nowaSkoraDialog();
		void keyPressEvent(QKeyEvent *event) {
			if (event->key() == Qt::Key_Escape) {
				wyczyscPola();
			}
			QDialog::keyPressEvent(event);
		}
		void wyczyscPola();
		QString getNaz() const;

		QString getDos() const;

		double getCena() const;

	private slots:
		void on_buttonBox_accepted();

		void on_buttonBox_rejected();

	private:
		Ui::nowaSkoraDialog *ui;
		QString naz;
		QString dos;
		double cena;
};

#endif // NOWASKORADIALOG_H
