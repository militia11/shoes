#include "WybHandlDialog.h"
#include "ui_WybHandlDialog.h"

WybHandlDialog::WybHandlDialog(BazaDanychManager *db,QWidget *parent) :
	QDialog(parent),
	dbManager(db),
	ui(new Ui::WybHandlDialog)
	{
	ui->setupUi(this);
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
	SLOT(akceptujHandl(const QModelIndex)));
	}

WybHandlDialog::~WybHandlDialog()
	{
	delete ui;
	}

void WybHandlDialog::aktualizujTabele()
	{
	ui->tableView->setModel(dbManager->getModelHandlowce());
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
//	ui->tableView->setColumnWidth(1, 200);
//	ui->tableView->setColumnWidth(2, 135);
	}

QString WybHandlDialog::getAktualnyHandlNazwa() {
	return  aktualnyHandlNazwa;
	}

void WybHandlDialog::akceptujHandl(const QModelIndex index)
	{
	dbManager->ustawIdAktualnegoHandl(index);
	 aktualnyHandlNazwa = dbManager->pobierzNazweAktualnegoHandl();
	 accept();

	}

void WybHandlDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	ui->lineEditNazwaSkrot->clear();
	ui->lineEditSkrot->clear();
	ui->pushSzukaj->click();
	}
