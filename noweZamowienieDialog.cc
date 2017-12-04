#include "noweZamowienieDialog.h"
#include "ui_noweZamowienieDialog.h"

noweZamowienieDialog::noweZamowienieDialog(WybKlientaDialog *dialog,
		QWidget *parent) :
	QDialog(parent),
	dialog(dialog),
	ui(new Ui::noweZamowienieDialog)
{
	ui->setupUi(this);
}

noweZamowienieDialog::~noweZamowienieDialog()
{
	delete ui;
}

void noweZamowienieDialog::on_pushButton_3_clicked()
{	// wyszukaj klienta
	dialog->exec();
}

void noweZamowienieDialog::on_pushButton_clicked()
{	// dodaj klienta

}
