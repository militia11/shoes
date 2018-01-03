#include "WybModelDialog.h"
#include "ui_WybModelDialog.h"

WybModelDialog::WybModelDialog(BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	dbManager(db),
	ui(new Ui::WybModelDialog)
{
	ui->setupUi(this);
	proxy = new QSortFilterProxyModel(this);
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		SLOT(akceptujModel(const QModelIndex)));
}

WybModelDialog::~WybModelDialog()
{	delete proxy;
	delete ui;
}

void WybModelDialog::akceptujModel(const QModelIndex index) {
	QModelIndex  idx = proxy->mapToSource(
				   ui->tableView->selectionModel()->currentIndex());
	dbManager->ustawAktualnyModelId(idx);
	accept();
}

void WybModelDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	dbManager->setModeleWybieranie();
	aktualizujTabele();
}

void WybModelDialog::aktualizujTabele()
{	proxy->setSourceModel(dbManager->getModelmModeleWybieranie());
	proxy->setDynamicSortFilter(true);
	ui->tableView->setModel(proxy);
	ui->tableView->setSortingEnabled(true);
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setSectionHidden(8, true);
	hv->setSectionHidden(9, true);
	hv->setSectionHidden(10, true);
	hv->setSectionHidden(11, true);
	hv->setSectionHidden(14, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
	//	ui->tableView->setColumnWidth(1, 200);
	//	ui->tableView->setColumnWidth(2, 135);
}
