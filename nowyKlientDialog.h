#ifndef NOWYKLIENTDIALOG_H
#define NOWYKLIENTDIALOG_H

#include <QtWidgets/QDialog>
#include <QRegExp>

namespace Ui {
class nowyKlientDialog;
}

class nowyKlientDialog : public QDialog
	{
		Q_OBJECT

	protected:
		void showEvent(QEvent *e);
	public:
		explicit nowyKlientDialog(QWidget *parent = 0);
		~nowyKlientDialog();

		QString getNazwa() const;
		QString getSkrot() const;
		QString getNumerTelefonu() const;
		QString getUlica() const;
		QString getNumerDomu() const;
		QString getMiasto() const;
		QString getKodPocztowy() const;
		void setNazwa(QString noweImie);
		void setSkrot(QString noweNazwisko);
		void setNumerTelefonu(QString nowyNumerTel);
		void setUlica(QString nowaUlica);
		void setNumerDomu(QString nowyNumerDomu);
		void setMiasto(QString noweMiasto);
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

	private slots:
		void on_buttonBox_accepted();
		void on_buttonBox_rejected();

	private:
		Ui::nowyKlientDialog *ui;
		static QRegExp formatNrTelefonu;
		QString nazwa;
		QString skrot;
		QString numerTelefonu;
		QString numerDomu;
		QString miasto;
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
		void setResetujPrzyciskiWymagane();
	};

#endif // NOWYKLIENTDIALOG_H
