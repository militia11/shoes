#ifndef NOWEZAMOWIENIEDIALOG_H
#define NOWEZAMOWIENIEDIALOG_H

#include <QtWidgets/QDialog>

namespace Ui {
class noweZamowienieDialog;
}

class noweZamowienieDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit noweZamowienieDialog(QWidget *parent = 0);
		~noweZamowienieDialog();

	private:
		Ui::noweZamowienieDialog *ui;
	};

#endif // NOWEZAMOWIENIEDIALOG_H
