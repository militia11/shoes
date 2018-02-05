#include "nowaSkoraDialog.h"
#include "ui_nowaSkoraDialog.h"
#include <QMessageBox>
nowaSkoraDialog::nowaSkoraDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::nowaSkoraDialog), cena(0.0)
{
	ui->setupUi(this);
}

nowaSkoraDialog::~nowaSkoraDialog() {
	delete ui;
}

void nowaSkoraDialog::wyczyscPola() {
	ui->lineEditNaz->clear();
	ui->lineEditDost->clear();
	ui->lineEditCen->clear();
}

void nowaSkoraDialog::on_buttonBox_accepted() {
	if (!ui->lineEditNaz->text().isEmpty()) {
		naz = ui->lineEditNaz->text();
		dos = ui->lineEditDost->text();
		cena = ui->lineEditCen->text().toDouble();
		wyczyscPola();
		accept();
	} else {
		QMessageBox::warning(this, "BRAK WYMAGANEGO POLA",
					 QString(" <FONT COLOR='#000080'>Podaj nazwe skóry."),
					 QMessageBox::Ok);
	}
}

void nowaSkoraDialog::on_buttonBox_rejected() {
	wyczyscPola();
	reject();
}

double nowaSkoraDialog::getCena() const
{
	return cena;
}

QString nowaSkoraDialog::getDos() const
{
	return dos;
}

QString nowaSkoraDialog::getNaz() const
{
	return naz;
}
