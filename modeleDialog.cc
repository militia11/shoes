#include "modeleDialog.h"
#include "ui_modeleDialog.h"
#include  <QSqlRelationalDelegate>

modeleDialog::modeleDialog(NowyModelDialog *nowyModDialog,
			   BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::modeleDialog), dbManager(db), nowyModDialog(nowyModDialog),
	proxy(nullptr)
{
	ui->setupUi(this);
	clickableLabel label1;
	ui->horizontalLay1->addWidget(&label1);
	proxy = new QSortFilterProxyModel(this);
}

modeleDialog::~modeleDialog()
{
	delete ui;
	delete proxy;
}

void modeleDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	dbManager->setModele();
	proxy->setDynamicSortFilter(true);
	proxy->setSourceModel(dbManager->getModele());
	ui->tableView->setModel(proxy);
	ui->tableView->setSortingEnabled(true);
	for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
		ui->tableView->horizontalHeader()->setSectionResizeMode(c,
				QHeaderView::ResizeToContents);
	}
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setStretchLastSection(true);
	//hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
	//ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
}

void modeleDialog::on_pushButton_2_clicked() {
	nowyModDialog->setFixedSize(nowyModDialog->size());
	if ( nowyModDialog->exec() == QDialog::Accepted ) {
		//dbManager->zachowajModel(nowyKliDialog->getNazwa());
	}
}
