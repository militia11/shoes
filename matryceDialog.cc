#include "matryceDialog.h"
#include "ui_matryceDialog.h"
#include <QInputDialog>


matryceDialog::matryceDialog(NowaMatrycaDialog *nowamat, BazaDanychManager *db,
				 QWidget *parent) :
	QDialog(parent),
	ui(new Ui::matryceDialog), dbManager(db), nowamat(nowamat), proxy(nullptr),
	wybieranie(false)
{
	ui->setupUi(this);
	proxy = new QSortFilterProxyModel(this);
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		SLOT(wybranoMatryce(const QModelIndex)));
}

matryceDialog::~matryceDialog()
{
	delete ui;
	delete proxy;
}

void matryceDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	dbManager->setMatryce();
	proxy->setDynamicSortFilter(true);
	proxy->setSourceModel(dbManager->getMatryce());
	ui->tableView->setModel(proxy);
	for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
		ui->tableView->horizontalHeader()->setSectionResizeMode(c,
				QHeaderView::ResizeToContents);
	}
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
}

QString matryceDialog::getAktualnaMatrycaNazwa() const
{
	return aktualnaMatrycaNazwa;
}

void matryceDialog::on_pushButton_2_clicked() {
	if ( nowamat->exec() == QDialog::Accepted ) {
		dbManager->zachowajMatryce(nowamat->getNazwa(),
					   nowamat->getInfonazwa());
	}
}

void matryceDialog::wybranoMatryce(const QModelIndex index)
{
	QModelIndex  idx = proxy->mapToSource(
				   ui->tableView->selectionModel()->currentIndex());
	dbManager->setNazwaMatrycy(idx);
	aktualnaMatrycaNazwa = dbManager->getNazwaMatrycy();
	accept();
}

int matryceDialog::selectExec() {
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	return QDialog::exec();
}

int matryceDialog::exec() {
	ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
	return QDialog::exec();
}
