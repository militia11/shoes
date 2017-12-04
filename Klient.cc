#include "Klient.h"

Klient::Klient(QString nazwa, QString skrot, QString ulica, QString numerDomu, QString miasto, QString kodPocztowy, QString tel1, QString tel2, QString fax, QString mail, QString uwagi, QString numerTelefon)
    : nazwa(nazwa),
      skrot(skrot),
      ulica(ulica),
      numerDomu(numerDomu),
      miasto(miasto),
      kodPocztowy(kodPocztowy),
	  tel1(tel1),
	  tel2(tel2),
	  fax(fax),
	  mail(mail),
	  uwagi(uwagi),
	  numerTelefonu(numerTelefon){}

QString Klient::getNazwa() const
{
    return nazwa;
}

QString Klient::getSkrot() const
{
    return skrot;
}

QString Klient::getUlica() const
{
    return ulica;
}

QString Klient::getNumerDomu() const
{
    return numerDomu;
}

QString Klient::getMiasto() const
{
    return miasto;
}

QString Klient::getKodPocztowy() const
{
    return kodPocztowy;
}

void Klient::setNazwa(QString nowaNazwa)
{
    nazwa = nowaNazwa;
}

void Klient::setSkrot(QString nowySkrot)
{
    skrot = nowySkrot;
}

void Klient::setNumerTelefonu(QString nowyNumerTel)
{
    numerTelefonu = nowyNumerTel;
}

void Klient::setUlica(QString nowaUlica)
{
    ulica = nowaUlica;
}

void Klient::setNumerDomu(QString nowyNumerDomu)
{
    numerDomu = nowyNumerDomu;
}

void Klient::setMiasto(QString noweMiasto)
{
    miasto = noweMiasto;
}

void Klient::setKodPocztowy(QString nowyKodPocztowy)
{
    kodPocztowy = nowyKodPocztowy;
}

QString Klient::getNumerTelefonu() const
{
    return numerTelefonu;
}

QString Klient::toString() const
{
	return QString("ID: %1  %2 %3  %4 %5 %6").arg(nazwa).arg(skrot).arg(ulica).arg(numerDomu).arg(kodPocztowy).arg(miasto);
}

QString Klient::getTel1() const
	{
	return tel1;
	}

void Klient::setTel1(const QString &value)
	{
	tel1 = value;
	}

QString Klient::getTel2() const
	{
	return tel2;
	}

void Klient::setTel2(const QString &value)
	{
	tel2 = value;
	}

QString Klient::getFax() const
	{
	return fax;
	}

void Klient::setFax(const QString &value)
	{
	fax = value;
	}

QString Klient::getMail() const
	{
	return mail;
	}

void Klient::setMail(const QString &value)
	{
	mail = value;
	}

QString Klient::getUwagi() const
	{
	return uwagi;
	}

void Klient::setUwagi(const QString &value)
	{
	uwagi = value;
	}

int Klient::getZamowione() const
	{
	return zamowione;
	}

void Klient::setZamowione(int value)
	{
	zamowione = value;
	}

int Klient::getOdebrane() const
	{
	return odebrane;
	}

void Klient::setOdebrane(int value)
	{
	odebrane = value;
	}

int Klient::getNieodebrane() const
	{
	return nieodebrane;
	}

void Klient::setNieodebrane(int value)
	{
	nieodebrane = value;
	}
