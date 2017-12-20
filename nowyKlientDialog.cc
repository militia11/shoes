#include "nowyKlientDialog.h"
#include "ui_nowyKlientDialog.h"
#include <QMessageBox>
#include <QDebug>

QRegExp nowyKlientDialog::formatNrTelefonu("([1-9]\\d\\d)-(\\d{3})-(\\d{3})");

void nowyKlientDialog::resetujPrzyciskiWymagane()
{
	ui->lineEditNazwa->setStyleSheet("color:darkblue ;background-color: white;");
	ui->lineEditSkrot->setStyleSheet("color:darkblue ;background-color: white;");
	ui->lineEditNrDomu->setStyleSheet("color:darkblue ;background-color: white;");
	ui->lineEditMiasto->setStyleSheet("color:darkblue ;background-color: white;");
	ui->lineEditKodPocztowy->setStyleSheet("color:darkblue ;background-color: white;");
	ui->lineEditUlica->setStyleSheet("color:darkblue ;background-color: white;");
}

nowyKlientDialog::nowyKlientDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::nowyKlientDialog) {
	ui->setupUi(this);
	resetujPrzyciskiWymagane();
}

nowyKlientDialog::~nowyKlientDialog() {
	delete ui;
}
void nowyKlientDialog::wyczyscPola()
{
	ui->lineEditNazwa->clear();
	ui->lineEditSkrot->clear();
	ui->lineEditNrDomu->clear();
	ui->lineEditMiasto->clear();
	ui->lineEditKodPocztowy->clear();
	ui->lineEditUlica->clear();
	ui->lineEditFax->clear();
	ui->lineEditTel1->clear();
	ui->lineEditTel2->clear();
	ui->lineEditNumerTelefonu->clear();
	ui->lineEditMail->clear();
	ui->lineEditUwagi->clear();
}

void nowyKlientDialog::on_buttonBox_accepted() {
	bool wyswietlKomunikat = false;

	resetujPrzyciskiWymagane();
	if (ui->lineEditNrDomu->text().isEmpty()) {
		ui->lineEditNrDomu->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		wyswietlKomunikat = true;
		ui->lineEditNrDomu->setFocus();
	}
	if (ui->lineEditUlica->text().isEmpty()) {
		ui->lineEditUlica->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		wyswietlKomunikat = true;
		ui->lineEditUlica->setFocus();
	}
	if (ui->lineEditKodPocztowy->text().isEmpty()) {
		ui->lineEditKodPocztowy->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		wyswietlKomunikat = true;
		ui->lineEditKodPocztowy->setFocus();
	}
	if (ui->lineEditMiasto->text().isEmpty()) {
		ui->lineEditMiasto->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		wyswietlKomunikat = true;
		ui->lineEditMiasto->setFocus();
	}
	if (ui->lineEditSkrot->text().isEmpty() ) {
		wyswietlKomunikat = true;
		ui->lineEditSkrot->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		ui->lineEditSkrot->setFocus();
	}

	if (ui->lineEditNazwa->text().isEmpty() ) {
		ui->lineEditNazwa->setFocus();
		ui->lineEditNazwa->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		wyswietlKomunikat = true;
	}

	if (wyswietlKomunikat) {
		QMessageBox::warning( this, "BRAK WYMAGANYCH PÓL",
					  " <FONT COLOR='#000080'>Nie można zaakceptować bez podania wymaganych pól. "
					  "<br>Proszę uzupełnić podświetlone na czerwono pola.</FONT>",
					  QMessageBox::Ok);
	} else {
		nazwa = ui->lineEditNazwa->text();
		skrot = ui->lineEditSkrot->text();
		numerDomu = ui->lineEditNrDomu->text();
		miasto = ui->lineEditMiasto->text();
		kodPocztowy = ui->lineEditKodPocztowy->text();
		ulica = ui->lineEditUlica->text();
		fax = ui->lineEditFax->text();
		tel1 = ui->lineEditTel1->text();
		tel2 = ui->lineEditTel2->text();
		numerTelefonu = ui->lineEditNumerTelefonu->text();
		mail = ui->lineEditMail->text();
		uwagi = ui->lineEditUwagi->text();

		wyczyscPola();
		resetujPrzyciskiWymagane();
		accept();
	}
}

void nowyKlientDialog::on_buttonBox_rejected()
{
	wyczyscPola();
	resetujPrzyciskiWymagane();
	reject();
}


QString nowyKlientDialog::getNazwa() const
{
	return nazwa;
}

QString nowyKlientDialog::getSkrot() const
{
	return skrot;
}

QString nowyKlientDialog::getUlica() const
{
	return ulica;
}

QString nowyKlientDialog::getNumerDomu() const
{
	return numerDomu;
}

QString nowyKlientDialog::getMiasto() const
{
	return miasto;
}

QString nowyKlientDialog::getKodPocztowy() const
{
	return kodPocztowy;
}

void nowyKlientDialog::setNazwa(QString nowaNazwa)
{
	nazwa = nowaNazwa;
}

void nowyKlientDialog::setSkrot(QString nowySkrot)
{
	skrot = nowySkrot;
}

void nowyKlientDialog::setNumerTelefonu(QString nowyNumerTel)
{
	numerTelefonu = nowyNumerTel;
}

void nowyKlientDialog::setUlica(QString nowaUlica)
{
	ulica = nowaUlica;
}

void nowyKlientDialog::setNumerDomu(QString nowyNumerDomu)
{
	numerDomu = nowyNumerDomu;
}

void nowyKlientDialog::setMiasto(QString noweMiasto)
{
	miasto = noweMiasto;
}

void nowyKlientDialog::setKodPocztowy(QString nowyKodPocztowy)
{
	kodPocztowy = nowyKodPocztowy;
}

QString nowyKlientDialog::getNumerTelefonu() const
{
	return numerTelefonu;
}

QString nowyKlientDialog::getTel1() const
{
	return tel1;
}

void nowyKlientDialog::setTel1(const QString &value)
{
	tel1 = value;
}

QString nowyKlientDialog::getTel2() const
{
	return tel2;
}

void nowyKlientDialog::setTel2(const QString &value)
{
	tel2 = value;
}

QString nowyKlientDialog::getFax() const
{
	return fax;
}

void nowyKlientDialog::setFax(const QString &value)
{
	fax = value;
}

QString nowyKlientDialog::getMail() const
{
	return mail;
}

void nowyKlientDialog::setMail(const QString &value)
{
	mail = value;
}

QString nowyKlientDialog::getUwagi() const
{
	return uwagi;
}

void nowyKlientDialog::setUwagi(const QString &value)
{
	uwagi = value;
}

int nowyKlientDialog::getZamowione() const
{
	return zamowione;
}

void nowyKlientDialog::setZamowione(int value)
{
	zamowione = value;
}

int nowyKlientDialog::getOdebrane() const
{
	return odebrane;
}

void nowyKlientDialog::setOdebrane(int value)
{
	odebrane = value;
}

int nowyKlientDialog::getNieodebrane() const
{
	return nieodebrane;
}

void nowyKlientDialog::setNieodebrane(int value)
{
	nieodebrane = value;
}
