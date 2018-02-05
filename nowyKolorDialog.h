#ifndef NOWYKOLORDIALOG_H
#define NOWYKOLORDIALOG_H

#include <QtWidgets/QDialog>
#include <QKeyEvent>
namespace Ui {
class nowyKolorDialog;
}

class nowyKolorDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit nowyKolorDialog(QWidget *parent = 0);
		~nowyKolorDialog();
		void keyPressEvent(QKeyEvent *event) {
			if (event->key() == Qt::Key_Escape) {
				wyczyscPola();
			}
			QDialog::keyPressEvent(event);
		}
		void wyczyscPola();
		QString getSk1() const;
		void setSk1(const QString &value);

		int getAktualnyKolor() const;

		QString getSk1d() const;

		QString getSk2() const;

		QString getSk2d() const;

		QString getSk3() const;

		QString getSk3d() const;

		QString getSkdomi() const;

	private slots:
		void on_buttonBox_accepted();

		void on_buttonBox_rejected();

	private:
		Ui::nowyKolorDialog *ui;
		int aktKolor;
		QString sk1;
		QString sk1d;
		QString sk2;
		QString sk2d;
		QString sk3;
		QString sk3d;
		QString skdomin;

};

#endif // NOWYKOLORDIALOG_H
