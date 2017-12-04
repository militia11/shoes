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

void WybKlientaDialog::setTable()
{
	ui->tableView->setModel(db->getModelKlienciWyb());
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
}

void WybKlientaDialog::showEvent(QShowEvent *e) {

}
