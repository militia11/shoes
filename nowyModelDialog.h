#ifndef NOWYMODELDIALOG_H
#define NOWYMODELDIALOG_H

#include <QtWidgets/QDialog>


namespace Ui {
	class nowyModelDialog;
}

class nowyModelDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit nowyModelDialog(QWidget *parent = 0);
		~nowyModelDialog();

	private:
		Ui::nowyModelDialog *ui;
	};

#endif // NOWYMODELDIALOG_H
