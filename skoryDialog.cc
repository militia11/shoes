#include "skoryDialog.h"
#include "ui_skoryDialog.h"

skoryDialog::skoryDialog(BazaDanychManager *db,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::skoryDialog),dbManager(db)
	{
		ui->setupUi(this);
	}

skoryDialog::~skoryDialog()
	{
		delete ui;
	}
void skoryDialog::showEvent(QShowEvent *e)
	{
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
