#include "WybHandlDialog.h"
#include "ui_WybHandlDialog.h"

WybHandlDialog::WybHandlDialog(BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	dbManager(db),
	ui(new Ui::WybHandlDialog)
{
	ui->setupUi(this);
	proxy = new QSortFilterProxyModel(this);
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		SLOT(akceptujHandl(const QModelIndex)));
}

WybHandlDialog::~WybHandlDialog()
{	delete proxy;
	delete ui;
}

void WybHandlDialog::aktualizujTabele() {
	proxy->setSourceModel(dbManager->getModelHandlowceWybieranie());
	proxy->setDynamicSortFilter(true);
	ui->tableView->setModel(proxy);
	ui->tableView->setSortingEnabled(true);
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setStretchLastSection(true);
	//hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
}

QString WybHandlDialog::getAktualnyHandlNazwa() {
	return aktualnyHandlNazwa;
}

void WybHandlDialog::akceptujHandl(const QModelIndex index) {
	QModelIndex  idx = proxy->mapToSource(
				   ui->tableView->selectionModel()->currentIndex());
	dbManager->ustawIdAktualnegoHandl(idx);
	aktualnyHandlNazwa = dbManager->pobierzNazweAktualnegoHandl();
	accept();
}

void WybHandlDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	dbManager->setHandlowceWybieranie();
	aktualizujTabele();
	ui->lineEditNazwaSkrot->clear();
	ui->lineEditSkrot->clear();
}

void WybHandlDialog::on_pushButton_clicked() {

}
