#include "matryceDialog.h"
#include "ui_matryceDialog.h"

matryceDialog::matryceDialog(BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::matryceDialog), dbManager(db)
{
	ui->setupUi(this);
}

matryceDialog::~matryceDialog()
{
	delete ui;
}

void matryceDialog::showEvent(QShowEvent *e) {
	//		Q_UNUSED(e);
	//		dbManager->setKlienci();
	//		ui->tableViewKlienci->setModel(dbManager->getModelKlienci());
	//		for (int c = 0; c < ui->tableViewKlienci->horizontalHeader()->count(); ++c) {
	//		r	ui->tableViewKlienci->horizontalHeader()->setSectionResizeMode(c, QHeaderView::ResizeToContents);
	//		}
	//		QHeaderView *hv = ui->tableViewKlienci->horizontalHeader();
	//		hv->setStretchLastSection(true);
	//		hv->setSectionHidden(0, true);
	//		hv->setDefaultAlignment(Qt::AlignLeft);
}
