#include "handlowceDialog.h"
#include "ui_handlowceDialog.h"

handlowceDialog::handlowceDialog(NowyHandlowiecDialog *nowyKliDialog,
				 BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::handlowceDialog), dbManager(db), nowyKliDialog(nowyKliDialog),
	proxy(nullptr)
{
	ui->setupUi(this);
	proxy = new QSortFilterProxyModel(this);
}

handlowceDialog::~handlowceDialog()
{
	delete proxy;
	delete ui;
}

void handlowceDialog::showEvent(QShowEvent *e)
{
	Q_UNUSED(e);
	dbManager->setHandlowce();
	proxy->setDynamicSortFilter(true);
	proxy->setSourceModel(dbManager->getModelHandlowce());
	ui->tableViewHandlowce->setModel(proxy);
	ui->tableViewHandlowce->setSortingEnabled(true);
	for (int c = 0; c < ui->tableViewHandlowce->horizontalHeader()->count(); ++c) {
		ui->tableViewHandlowce->horizontalHeader()->setSectionResizeMode(c,
				QHeaderView::ResizeToContents);
	}
	QHeaderView *hv = ui->tableViewHandlowce->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
}

void handlowceDialog::on_pushButton_3_clicked()
{
	if ( nowyKliDialog->exec() == QDialog::Accepted ) {
		dbManager->zachowajHandlowca(nowyKliDialog->getImie(),
						 nowyKliDialog->getNazwisko(), nowyKliDialog->getSkrot());
	}
}
