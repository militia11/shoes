#include "koloryDialog.h"
#include "ui_koloryDialog.h"

koloryDialog::koloryDialog(BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::koloryDialog), dbManager(db), proxy(nullptr)
{
	ui->setupUi(this);
	proxy = new QSortFilterProxyModel(this);
}

koloryDialog::~koloryDialog()
{
	delete ui;
	delete proxy;
}

void koloryDialog::showEvent(QShowEvent *e)
{
	//	Q_UNUSED(e);
	//	dbManager->setKlienci();
	//	proxy->setDynamicSortFilter(true);
	//	proxy->setSourceModel(dbManager->getModelKlienci());
	//	ui->tableViewKlienci->setModel(proxy);
	//	ui->tableViewKlienci->setSortingEnabled(true);
	//	for (int c = 0; c < ui->tableViewKlienci->horizontalHeader()->count(); ++c) {
	//		ui->tableViewKlienci->horizontalHeader()->setSectionResizeMode(c,
	//				QHeaderView::ResizeToContents);
	//	}
	//	QHeaderView *hv = ui->tableViewKlienci->horizontalHeader();
	//	hv->setStretchLastSection(true);
	//	//hv->setSectionHidden(0, true);
	//	//	hv->setSectionHidden(13, true);
	//	//	hv->setSectionHidden(14, true);
	//	//	hv->setSectionHidden(15, true);
	//	hv->setDefaultAlignment(Qt::AlignLeft);
}

void koloryDialog::on_pushButton_2_clicked()
{

}
