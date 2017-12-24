#include "klienciDialog.h"
#include "ui_klienciDialog.h"

klienciDialog::klienciDialog(nowyKlientDialog *nowyKliDialog,
				 BazaDanychManager *db, QWidget *parent) :
	QDialog(parent), ui(new Ui::klienciDialog), dbManager(db),
	nowyKliDialog(nowyKliDialog), proxy(nullptr)

{
	ui->setupUi(this);

}

klienciDialog::~klienciDialog()
{
	delete ui;
}

void klienciDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	dbManager->setKlienci();
	if (proxy == nullptr) {
		proxy = new QSortFilterProxyModel(this);
	}
	proxy->setDynamicSortFilter(true);
	proxy->setSourceModel(dbManager->getModelKlienci());
	ui->tableViewKlienci->setModel(proxy);
	ui->tableViewKlienci->setSortingEnabled(true);
	for (int c = 0; c < ui->tableViewKlienci->horizontalHeader()->count(); ++c) {
		ui->tableViewKlienci->horizontalHeader()->setSectionResizeMode(c,
				QHeaderView::ResizeToContents);
	}
	QHeaderView *hv = ui->tableViewKlienci->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setSectionHidden(13, true);
	hv->setSectionHidden(14, true);
	hv->setSectionHidden(15, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
}

void klienciDialog::hideEvent(QHideEvent *e) {
	delete proxy;
	proxy = 0;
}

void klienciDialog::on_pushButton_2_clicked() {
	if ( nowyKliDialog->exec() == QDialog::Accepted ) {
		Klient klient(nowyKliDialog->getNazwa(), nowyKliDialog->getSkrot(),
				  nowyKliDialog->getUlica(),
				  nowyKliDialog->getNumerDomu(),
				  nowyKliDialog->getMiasto(), nowyKliDialog->getKodPocztowy(),
				  nowyKliDialog->getTel1(),
				  nowyKliDialog->getTel2(),
				  nowyKliDialog->getFax(), nowyKliDialog->getMail(),
				  nowyKliDialog->getUwagi(),
				  nowyKliDialog->getNumerTelefonu());
		dbManager->zachowajKlienta(klient);
	}
}
