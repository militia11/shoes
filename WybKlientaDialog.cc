#include "WybKlientaDialog.h"
#include "ui_WybKlientaDialog.h"

WybKlientaDialog::WybKlientaDialog(BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	db(db),
	ui(new Ui::WybKlientaDialog)
{
	ui->setupUi(this);
}

WybKlientaDialog::~WybKlientaDialog()
{
	delete ui;
}

void WybKlientaDialog::showEvent(QShowEvent *e) {

}
