#include "nowySpodDialog.h"
#include "ui_nowySpodDialog.h"
#include <QDebug>
nowySpodDialog::nowySpodDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::nowySpodDialog)
{
	ui->setupUi(this);
	resetujPrzyciskiWymagane();
}

nowySpodDialog::~nowySpodDialog()
{
	delete ui;
}

void nowySpodDialog::on_pushButton_14_clicked() {
	images[0] = ManagerZdjec::getImage(this);
	if (!images[0].isNull()) {
		ui->labelPodglad1->setPixmap(QPixmap::fromImage(images[0]));
	}
}

void nowySpodDialog::on_pushButton_15_clicked() {
	images[1] = ManagerZdjec::getImage(this);
	if (!images[1].isNull()) {
		ui->labelPodglad2->setPixmap(QPixmap::fromImage(images[1]));
	}
}

void nowySpodDialog::on_pushButton_16_clicked() {
	images[2] = ManagerZdjec::getImage(this);
	if (!images[2].isNull()) {
		ui->labelPodglad3->setPixmap(QPixmap::fromImage(images[2]));
	}
}

void nowySpodDialog::on_pushButton_17_clicked()
{
	images[3] = ManagerZdjec::getImage(this);
	if (!images[3].isNull()) {
		ui->labelPodglad4->setPixmap(QPixmap::fromImage(images[3]));
	}
}

void nowySpodDialog::on_buttonBox_accepted() {
	bool wyswietlKomunikat = false;

	resetujPrzyciskiWymagane();
	if (ui->lineEditNaz->text().isEmpty() ) {
		ui->lineEditNaz->setFocus();
		ui->lineEditNaz->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		wyswietlKomunikat = true;
	}
	if (ui->lineEditProd->text().isEmpty() ) {
		ui->lineEditProd->setFocus();
		ui->lineEditProd->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
		wyswietlKomunikat = true;
	}

	if (wyswietlKomunikat) {
		QMessageBox::warning( this, "BRAK WYMAGANYCH PÓL",
					  " <FONT COLOR='#000080'>Nie można zaakceptować bez podania wymaganych pól. "
					  "<br>Proszę uzupełnić podświetlone na czerwono pola.</FONT>",
					  QMessageBox::Ok);
	} else {
		nazwa = ui->lineEditNaz->text();
		producent = ui->lineEditProd->text();
		rodzaj = ui->lineEditRodz->text();
		uwagi = ui->plainTextEdit->toPlainText();
		rozm = ui->lineEditRozm->text();
		wyczyscPola();
		resetujPrzyciskiWymagane();
		accept();
	}
}

void nowySpodDialog::on_buttonBox_rejected() {
	wyczyscPola();
	resetujPrzyciskiWymagane();
	reject();
}

void nowySpodDialog::showEvent(QShowEvent *e) {
	images.clear();
	for (int i = 0; i < 4; i++) {
		images.append(QImage());
	}
}

void nowySpodDialog::wyczyscPola() {
	ui->lineEditNaz->clear();
	ui->lineEditProd->clear();
	ui->lineEditRodz->clear();
	ui->plainTextEdit->clear();
	ui->lineEditRozm->clear();
	ui->labelPodglad1->clear();
	ui->labelPodglad2->clear();
	ui->labelPodglad3->clear();
	ui->labelPodglad4->clear();
}

void nowySpodDialog::resetujPrzyciskiWymagane() {
	ui->lineEditNaz->setStyleSheet("color:darkblue ;background-color: white;");
	ui->lineEditProd->setStyleSheet("color:darkblue ;background-color: white;");
}

QVector<QImage> nowySpodDialog::getImages() const
{
	return images;
}

QString nowySpodDialog::getRozm() const
{
	return rozm;
}

QString nowySpodDialog::getUwagi() const
{
	return uwagi;
}

QString nowySpodDialog::getRodzaj() const
{
	return rodzaj;
}

QString nowySpodDialog::getProducent() const
{
	return producent;
}

QString nowySpodDialog::getNazwa() const
{
	return nazwa;
}
