#ifndef KLIENT_H
#define KLIENT_H

#include <QtCore/qglobal.h>

#include <QString>

class Klient {
public:
    Klient(QString nazwa, QString skrot,QString ulica, QString numerDomu,
		   QString miasto, QString kodPocztowy,
		   QString tel1 , QString tel2, QString fax, QString mail, QString uwagi,  QString numerTelefon);
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

    QString toString() const;
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

private:
	QString nazwa;
	QString skrot;
	QString ulica;
	QString numerDomu;
	QString miasto;
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
