#include "koloryDialog.h"
#include "ui_koloryDialog.h"

koloryDialog::koloryDialog(nowyKolorDialog *dilogNowyKolor,
			   BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::koloryDialog), dbManager(db), proxy(nullptr),
	nowyKolor(dilogNowyKolor)
{
	ui->setupUi(this);
	proxy = new QSortFilterProxyModel(this);
	aktualnyKolor = -1;
	ui->lineEdit->setFixedWidth(94);
}

koloryDialog::~koloryDialog()
{
	delete ui;
	delete proxy;
}

void koloryDialog::ustawIFiltruj()
{
	dbManager->getKolory()->setFilter(QString("kolor LIKE '%1%'").arg(ui->lineEdit->text()));
}

int koloryDialog::selectExec()
{
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		SLOT(wybranoKolor(const QModelIndex)));
	return QDialog::exec();
}

void koloryDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	dbManager->setKolory();
	proxy->setDynamicSortFilter(true);
	proxy->setSourceModel(dbManager->getKolory());
	ui->tableView->setModel(proxy);
	ui->tableView->setSortingEnabled(true);
	for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
		ui->tableView->horizontalHeader()->setSectionResizeMode(c,
				QHeaderView::ResizeToContents);
	}
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
	ui->tableView->sortByColumn(0, Qt::AscendingOrder);
	ui->lineEdit->clear();
	ustawIFiltruj();
}

void koloryDialog::hideEvent(QHideEvent *e) {
	disconnect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		   SLOT(wybranoKolor(const QModelIndex)));
}

void koloryDialog::on_pushButton_2_clicked() {
	if ( nowyKolor->exec() == QDialog::Accepted ) {
		dbManager->zachowajKolor(nowyKolor->getAktualnyKolor(), nowyKolor->getSk1(),
					 nowyKolor->getSk1d(),
					 nowyKolor->getSk2(), nowyKolor->getSk2d(), nowyKolor->getSk3(),
					 nowyKolor->getSk3d(), nowyKolor->getSkdomi());
	}
}

void koloryDialog::wybranoKolor(const QModelIndex index) {
	QModelIndex  idx = proxy->mapToSource(
				   ui->tableView->selectionModel()->currentIndex());
	aktualnyKolor =	dbManager->pobierzAktualnyKolor(idx);
	accept();
}

int koloryDialog::exec() {
	ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
	return QDialog::exec();
}

int koloryDialog::getAktualnyKolor() const {
	return aktualnyKolor;
}

void koloryDialog::on_pushSzukaj_clicked()
{
	ustawIFiltruj();
}
