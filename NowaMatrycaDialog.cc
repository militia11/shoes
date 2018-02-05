#include "NowaMatrycaDialog.h"
#include "ui_NowaMatrycaDialog.h"
#include <QMessageBox>
NowaMatrycaDialog::NowaMatrycaDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NowaMatrycaDialog)
{
	ui->setupUi(this);
}

NowaMatrycaDialog::~NowaMatrycaDialog()
{
	delete ui;
}

void NowaMatrycaDialog::wyczyscPola()
{
	ui->lineEdit->clear();
	ui->plainTextEdit->clear();
}

QString NowaMatrycaDialog::getNazwa() const
{
	return nazwa;
}

void NowaMatrycaDialog::setNazwa(const QString &value)
{
	nazwa = value;
}

QString NowaMatrycaDialog::getInfonazwa() const
{
	return infonazwa;
}

void NowaMatrycaDialog::setInfonazwa(const QString &value)
{
	infonazwa = value;
}

void NowaMatrycaDialog::on_buttonBox_accepted()
{
	if (!ui->lineEdit->text().isEmpty()) {
		nazwa = ui->lineEdit->text();
		infonazwa = ui->plainTextEdit->toPlainText();
		wyczyscPola();
		accept();
	} else {
		QMessageBox::warning(this, "BRAK WYMAGANEGO POLA",
					 QString(" <FONT COLOR='#000080'>Podaj nazwę matrycy."),
					 QMessageBox::Ok);
	}
}

void NowaMatrycaDialog::on_buttonBox_rejected()
{
	wyczyscPola();
	reject();
}
