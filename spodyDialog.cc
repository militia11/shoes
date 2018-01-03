#include "spodyDialog.h"
#include "ui_spodyDialog.h"
#include "BazaDanychManager.h"
spodyDialog::spodyDialog(nowySpodDialog *dialogNSpod, BazaDanychManager *db,
			 QWidget *parent) :
	QDialog(parent),
	dialogNSpod(dialogNSpod),
	ui(new Ui::spodyDialog)
{
	ui->setupUi(this);
}

spodyDialog::~spodyDialog()
{
	delete ui;
}

void spodyDialog::showEvent(QShowEvent *e)
{

}

void spodyDialog::on_pushButton_2_clicked()
{
	dialogNSpod->setFixedSize(dialogNSpod->size());
	if (dialogNSpod->exec() == QDialog::Accepted ) {
	}
}
