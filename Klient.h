#ifndef KLIENT_H
#define KLIENT_H

#include <QtCore/qglobal.h>

#include <QString>

class Klient {
	public:
		Klient(QString nazwa, QString skrot, QString ulica, QString numerDomu,
			   QString miasto, QString kodPocztowy,
			   QString tel1 , QString tel2, QString fax, QString mail, QString uwagi,
               QString numerTelefon, QString woj);

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

		QString getKodPocztowy() const;
		void setKodPocztowy(QString nowyKodPocztowy);

		QString getMiasto() const;
		void setMiasto(QString noweMiasto);

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

private:
        QString nazwa;
        QString skrot;
        QString ulica;
        QString numerDomu;
		QString miasto;
        QString woj;
		QString kodPocztowy;
		QString tel1;
		QString tel2;
		QString fax;
		QString mail;
		QString uwagi;
		QString numerTelefonu;
		int zamowione;
		int odebrane;
		int nieodebrane;
};


#endif // KLIENT_H
