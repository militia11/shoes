#ifndef ZDJECIEDIALOG_H
#define ZDJECIEDIALOG_H

#include <QtWidgets/QDialog>

namespace Ui {
class ZdjecieDialog;
}

class ZdjecieDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit ZdjecieDialog(QWidget *parent = 0);
		~ZdjecieDialog();
		void setLabel(QImage im);

	private:
		Ui::ZdjecieDialog *ui;
};

#endif // ZDJECIEDIALOG_H
