#include "ocieplenieDialog.h"
#include "ui_ocieplenieDialog.h"
#include <QInputDialog>
ocieplenieDialog::ocieplenieDialog(BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ocieplenieDialog), dbManager(db) {
	ui->setupUi(this);
	proxy = new QSortFilterProxyModel(this);
}

ocieplenieDialog::~ocieplenieDialog() {
	delete ui;
	delete proxy;
}

void ocieplenieDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	dbManager->setOciep();
	proxy->setDynamicSortFilter(true);
	proxy->setSourceModel(dbManager->getOciep());
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
}

void ocieplenieDialog::hideEvent(QHideEvent *e)
{
	disconnect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		   SLOT(wybranoOc(const QModelIndex)));
}

QString ocieplenieDialog::getAktualnyKolor() const
{
	return aktualnyKolor;
}

int ocieplenieDialog::selectExec()
{
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		SLOT(wybranoOc(const QModelIndex)));
	return QDialog::exec();
}

void ocieplenieDialog::on_pushButton_2_clicked() {
	QString wzor = 0;

	wzor = QInputDialog::getText(this, tr("Dodaj ocieplenie"),
					 tr("Podaj rodzaj."), QLineEdit::Normal);
	if (wzor != 0) {
		dbManager->dodajOciep(wzor);
		dbManager->getOciep()->select();
	}
}

void ocieplenieDialog::wybranoOc(const QModelIndex index)
{
	QModelIndex  idx = proxy->mapToSource(
				   ui->tableView->selectionModel()->currentIndex());
	aktualnyKolor =	dbManager->pobierzAktualnyOciep(idx);
	accept();
}

int ocieplenieDialog::exec() {
	ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
	return QDialog::exec();
}
