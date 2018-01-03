#ifndef NOWAMATRYCADIALOG_H
#define NOWAMATRYCADIALOG_H

#include <QtWidgets/QDialog>
#include <QKeyEvent>
namespace Ui {
class NowaMatrycaDialog;
}

class NowaMatrycaDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit NowaMatrycaDialog(QWidget *parent = 0);
		~NowaMatrycaDialog();
		void keyPressEvent(QKeyEvent *event) {
			if (event->key() == Qt::Key_Escape) {
				wyczyscPola();
			}
			QDialog::keyPressEvent(event);
		}
		void wyczyscPola();
		QString getNazwa() const;
		void setNazwa(const QString &value);

		QString getInfonazwa() const;
		void setInfonazwa(const QString &value);

	private slots:
		void on_buttonBox_accepted();

		void on_buttonBox_rejected();

	private:
		Ui::NowaMatrycaDialog *ui;
		QString nazwa;
		QString infonazwa;
};

#endif // NOWAMATRYCADIALOG_H
