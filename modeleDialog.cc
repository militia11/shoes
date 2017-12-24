#include "modeleDialog.h"
#include "ui_modeleDialog.h"

modeleDialog::modeleDialog(nowyModelDialog *nowyKliDialog,BazaDanychManager *db,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::modeleDialog),dbManager(db),nowyKliDialog(nowyKliDialog)
	{
		ui->setupUi(this);
	}

modeleDialog::~modeleDialog()
	{
		delete ui;
	}

void modeleDialog::showEvent(QShowEvent *e){
		Q_UNUSED(e);
//		dbManager->setModele();
//		ui->tableViewKlienci->setModel(dbManager->getModelKlienci());
//		for (int c = 0; c < ui->tableViewKlienci->horizontalHeader()->count(); ++c) {
//			ui->tableViewKlienci->horizontalHeader()->setSectionResizeMode(c, QHeaderView::ResizeToContents);
//		}
//		QHeaderView *hv = ui->tableViewKlienci->horizontalHeader();
//		hv->setStretchLastSection(true);
//		hv->setSectionHidden(0, true);
//		hv->setDefaultAlignment(Qt::AlignLeft);
	}

void modeleDialog::on_pushButton_2_clicked() {
	if ( nowyKliDialog->exec()== QDialog::Accepted ) {

		}
}
