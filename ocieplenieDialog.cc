#include "ocieplenieDialog.h"
#include "ui_ocieplenieDialog.h"

ocieplenieDialog::ocieplenieDialog(BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ocieplenieDialog), dbManager(db) {
	ui->setupUi(this);
}

ocieplenieDialog::~ocieplenieDialog() {
	delete ui;
}

void ocieplenieDialog::showEvent(QShowEvent *e) {
	//		Q_UNUSED(e);
	//		dbManager->setKlienci();
	//		ui->tableViewKlienci->setModel(dbManager->getModelKlienci());
	//		for (int c = 0; c < ui->tableViewKlienci->horizontalHeader()->count(); ++c) {
	//			ui->tableViewKlienci->horizontalHeader()->setSectionResizeMode(c, QHeaderView::ResizeToContents);
	//		}
	//		QHeaderView *hv = ui->tableViewKlienci->horizontalHeader();
	//		hv->setStretchLastSection(true);
	//		hv->setSectionHidden(0, true);
	//		hv->setDefaultAlignment(Qt::AlignLeft);
}
