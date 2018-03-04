#ifndef NOWYKLIENTDIALOG_H
#define NOWYKLIENTDIALOG_H

#include <QtWidgets/QDialog>
#include <QKeyEvent>

namespace Ui {
class nowyKlientDialog;
}

class nowyKlientDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit nowyKlientDialog(QWidget *parent = 0);
		~nowyKlientDialog();

		QString getNazwa() const;
		void setNazwa(QString noweImie);

		QString getSkrot() const;
		void setSkrot(QString noweNazwisko);

		QString getNumerTelefonu() const;
		void setNumerTelefonu(QString nowyNumerTel);

		QString getUlica() const;
		void setUlica(QString nowaUlica);

		QString getNumerDomu() const;
		void setNumerDomu(QString nowyNumerDomu);

		QString getMiasto() const;
		void setMiasto(QString noweMiasto);

		QString getKodPocztowy() const;
		void setKodPocztowy(QString nowyKodPocztowy);

		QString getTel1() const;
		void setTel1(const QString &value);

		QString getTel2() const;
		void setTel2(const QString &value);

		QString getFax() const;
		void setFax(const QString &value);

		QString getMail() const;
		void setMail(const QString &value);

		QString getUwagi() const;
		void setUwagi(const QString &value);

		int getZamowione() const;
		void setZamowione(int value);

		int getOdebrane() const;
		void setOdebrane(int value);

		int getNieodebrane() const;
		void setNieodebrane(int value);

        QString getWoj() const;
        void setWoj(const QString &value);

private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();

	private:
		void keyPressEvent(QKeyEvent *event) {
			if (event->key() == Qt::Key_Escape) {
				wyczyscPola();
				resetujPrzyciskiWymagane();
			}
			QDialog::keyPressEvent(event);
		}
 void showEvent(QShowEvent *e);
		void wyczyscPola();
		void resetujPrzyciskiWymagane();

		Ui::nowyKlientDialog *ui;
		QString nazwa;
		QString skrot;
		QString numerTelefonu;
		QString numerDomu;
		QString miasto;
        QString woj;
		QString kodPocztowy;
		QString ulica;
		QString tel1;
		QString tel2;
		QString fax;
		QString mail;
		QString uwagi;
		int zamowione;
		int odebrane;
		int nieodebrane;

};

#endif // NOWYKLIENTDIALOG_H
