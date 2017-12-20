#include "WybModelDialog.h"
#include "ui_WybModelDialog.h"

WybModelDialog::WybModelDialog(BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	dbManager(db),
	ui(new Ui::WybModelDialog)
{
	ui->setupUi(this);
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		SLOT(akceptujModel(const QModelIndex)));
}

WybModelDialog::~WybModelDialog()
{
	delete ui;
}

void WybModelDialog::akceptujModel(const QModelIndex index) {
	dbManager->ustawAktualnyModelId(index);
	accept();
}

void WybModelDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
}

void WybModelDialog::aktualizujTabele()
{
	ui->tableView->setModel(dbManager->getModelmModeleWybieranie());
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
