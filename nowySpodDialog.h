#ifndef NOWYSPODDIALOG_H
#define NOWYSPODDIALOG_H

#if QT_VERSION >= 0x050000
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

namespace Ui {
	class nowySpodDialog;
}

class nowySpodDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit nowySpodDialog(QWidget *parent = 0);
		~nowySpodDialog();

	private:
		Ui::nowySpodDialog *ui;
	};

#endif // NOWYSPODDIALOG_H
