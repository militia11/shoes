#ifndef ROZNICEDIALOG_H
#define ROZNICEDIALOG_H
#include <QtWidgets/QDialog>


namespace Ui {
class RozniceDialog;
}

class RozniceDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit RozniceDialog(QWidget *parent = 0);
		~RozniceDialog();

	private:
		Ui::RozniceDialog *ui;
};

#endif // ROZNICEDIALOG_H
