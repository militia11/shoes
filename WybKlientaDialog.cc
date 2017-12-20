#include "WybKlientaDialog.h"
#include "ui_WybKlientaDialog.h"

WybKlientaDialog::WybKlientaDialog(BazaDanychManager *db, QWidget *parent) :
QDialog(parent),
dbManager(db),
ui(new Ui::WybKlientaDialog)
{
	ui->setupUi(this);
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
	SLOT(akceptujKlienta(const QModelIndex)));
}

WybKlientaDialog::~WybKlientaDialog()
{
	delete ui;
}

void WybKlientaDialog::aktualizujTabele()
{
	ui->tableView->setModel(dbManager->getModelKlienciWybieranie());
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
	ui->tableView->setColumnWidth(1, 200);
	ui->tableView->setColumnWidth(2, 135);
}

void WybKlientaDialog::akceptujKlienta(const QModelIndex index)
{
	dbManager->ustawIdAktualnegoKlienta(index);
	aktualnyKlientNazwa = dbManager->pobierzNazweAktualnegoKlienta();
	accept();
}

void WybKlientaDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	ui->lineEditNazwaSkrot->clear();
	ui->lineEditSkrot->clear();
	ui->pushSzukaj->click();
	// przenieść tu tworzenie w razie przeciążenia
}

QString WybKlientaDialog::getAktualnyKlientNazwa() const
{
	return aktualnyKlientNazwa;
}

void WybKlientaDialog::on_pushSzukaj_clicked()
{
	QString nazwa;
	QString nazwaSkrot;
	QAbstractItemModel *model = 0;
	if (ui->lineEditNazwaSkrot->text().isEmpty()) {
		ui->lineEditNazwaSkrot->text();
		if (ui->lineEditSkrot->text().isEmpty()) {
			ui->tableView->setModel(dbManager->getModelKlienci());
			return;
		} else {
			model = dbManager->wyszukajKlientowPoSkrocie(
			ui->lineEditSkrot->text());
		}
	} else {
		if (ui->lineEditSkrot->text().isEmpty()) {
			model = dbManager->wyszukajKlientowPoNazwie(
			ui->lineEditNazwaSkrot->text());
		} else {
			model = dbManager->wyszukajKlientow(
			ui->lineEditNazwaSkrot->text(), ui->lineEditSkrot->text());
		}
	}

	ui->tableView->setModel(model);
}

void WybKlientaDialog::on_pushButton_clicked()
{	ui->lineEditNazwaSkrot->setText("");
	ui->lineEditSkrot->setText("");
	ui->tableView->setModel(dbManager->getModelKlienci());
}
