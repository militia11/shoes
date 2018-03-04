#ifndef NOWYWZORDIALOG_H
#define NOWYWZORDIALOG_H

#include <QtWidgets/QDialog>
#include <QKeyEvent>
namespace Ui {
	class nowywzorDialog;
}

class nowywzorDialog : public QDialog
	{
		Q_OBJECT

	public:
		explicit nowywzorDialog(QWidget *parent = 0);
		~nowywzorDialog();

		QString getOpis() const;

		int getWzor() const;
		void keyPressEvent(QKeyEvent *event) {
			if (event->key() == Qt::Key_Escape) {
				wyczyscPola();
			}
			QDialog::keyPressEvent(event);
		}
		void wyczyscPola();
	private slots:
		void on_buttonBox_accepted();

		void on_buttonBox_rejected();

	private:
        void showEvent(QShowEvent *e);
		Ui::nowywzorDialog *ui;
		int wzor;
		QString opis;
	};

#endif // NOWYWZORDIALOG_H
