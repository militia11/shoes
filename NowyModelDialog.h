#ifndef NOWYMODELDIALOG_H
#define NOWYMODELDIALOG_H

#include <QtWidgets/QDialog>
#include "matryceDialog.h"

namespace Ui {
class NowyModelDialog;
}

class NowyModelDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit NowyModelDialog(matryceDialog *matryce, QWidget *parent = 0);
		~NowyModelDialog();

	private slots:
		void on_pushButton_9_clicked();

		void on_pushButton_14_clicked();

		void on_pushButton_15_clicked();

		void on_pushButton_16_clicked();

		void on_pushButton_17_clicked();

	private:
		QImage image1;
		Ui::NowyModelDialog *ui;
		matryceDialog *matryce;
};

#endif // NOWYMODELDIALOG_H
