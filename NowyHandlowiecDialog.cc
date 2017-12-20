#include "NowyHandlowiecDialog.h"
#include "ui_NowyHandlowiecDialog.h"
#include <QMessageBox>
NowyHandlowiecDialog::NowyHandlowiecDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NowyHandlowiecDialog)
{
	ui->setupUi(this);
	resetujPrzyciskiWymagane();
}

NowyHandlowiecDialog::~NowyHandlowiecDialog()
{
	delete ui;
}

void NowyHandlowiecDialog::on_buttonBox_accepted() {
	bool wyswietlKomunikat = false;

	resetujPrzyciskiWymagane();
	if (ui->lineEditSkrot_2->text().isEmpty() ) {
		ui->lineEditSkrot_2->setFocus();
		ui->lineEditSkrot_2->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		wyswietlKomunikat = true;
	}
	if (ui->lineEditImie->text().isEmpty() ) {
		ui->lineEditImie->setFocus();
		ui->lineEditImie->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		wyswietlKomunikat = true;
	}
	if (ui->lineEditNazwisko->text().isEmpty() ) {
		ui->lineEditNazwisko->setFocus();
		ui->lineEditNazwisko->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		wyswietlKomunikat = true;
	}
	if (wyswietlKomunikat) {
		QMessageBox::warning( this, "BRAK WYMAGANYCH PÓL",
					  " <FONT COLOR='#000080'>Nie można zaakceptować bez podania wymaganych pól. "
					  "<br>Proszę uzupełnić podświetlone na czerwono pola.</FONT>",
					  QMessageBox::Ok);
	} else {
		imie = ui->lineEditImie->text();
		nazwisko = ui->lineEditNazwisko->text();
		skrot = ui->lineEditSkrot_2->text();

		wyczyscPola();
		resetujPrzyciskiWymagane();
		accept();
	}
}

void NowyHandlowiecDialog::on_buttonBox_rejected()
{
	wyczyscPola();
	resetujPrzyciskiWymagane();
	reject();
}

void NowyHandlowiecDialog::wyczyscPola()
{
	ui->lineEditImie->clear();
	ui->lineEditNazwisko->clear();
	ui->lineEditSkrot_2->clear();
}

void NowyHandlowiecDialog::resetujPrzyciskiWymagane()
{
	ui->lineEditImie->setStyleSheet("color:darkblue ;background-color: white;");
	ui->lineEditNazwisko->setStyleSheet("color:darkblue ;background-color: white;");
	ui->lineEditSkrot_2->setStyleSheet("color:darkblue ;background-color: white;");
}
QString NowyHandlowiecDialog::getSkrot() const
{
	return skrot;
}

QString NowyHandlowiecDialog::getNazwisko() const
{
	return nazwisko;
}

QString NowyHandlowiecDialog::getImie() const
{
	return imie;
}
