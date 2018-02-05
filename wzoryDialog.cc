#include "wzoryDialog.h"
#include "ui_wzoryDialog.h"

wzoryDialog::wzoryDialog(nowywzorDialog * nw,BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::wzoryDialog), dbManager(db),nw(nw)
{
	ui->setupUi(this);
	proxy = new QSortFilterProxyModel(this);
	aktualnyWzorNr = -1;
}

wzoryDialog::~wzoryDialog()
{	delete proxy;
	delete ui;
}

int wzoryDialog::selectExec()
{
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		SLOT(wybranoWzor(const QModelIndex)));
	return QDialog::exec();
}

int wzoryDialog::exec()
{
	ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
	return QDialog::exec();
}

void wzoryDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	dbManager->setWzory();
	proxy->setSourceModel(dbManager->getWzory());
	proxy->setDynamicSortFilter(true);
	ui->tableView->setModel(proxy);
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignCenter);
	hv->setStretchLastSection(true);
	ui->tableView->sortByColumn(0, Qt::AscendingOrder);
}

void wzoryDialog::hideEvent(QHideEvent *e) {
	disconnect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		   SLOT(wybranoWzor(const QModelIndex)));
}

int wzoryDialog::getAktualnyWzorNr() const {
	return aktualnyWzorNr;
}

void wzoryDialog::on_pushButton_2_clicked() {
		if (nw->exec() == QDialog::Accepted) {
				dbManager->dodajWzor(nw->getWzor(), nw->getOpis());
				dbManager->getWzory()->select();
		}

}

void wzoryDialog::wybranoWzor(const QModelIndex index)
{
	QModelIndex  idx = proxy->mapToSource(
				   ui->tableView->selectionModel()->currentIndex());
	aktualnyWzorNr = dbManager->getNrWzoru(idx);
	accept();
}
