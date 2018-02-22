#include "DoRozkrojuDialog.h"
#include "ui_DoRozkrojuDialog.h"
#include "Delegate.h"
#include "DelegateArrows.h"
DoRozkrojuDialog::DoRozkrojuDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DoRozkrojuDialog), model(nullptr)
{
	ui->setupUi(this);
	NotEditableDelegate *del = new NotEditableDelegate(this);
	for (int i = 0; i < 10; i++) {
		ui->tableViewZam->setItemDelegateForColumn(i, del);
	}
	for (int i = 25; i < 33; i++) {
		ui->tableViewZam->setItemDelegateForColumn(i, del);
	}
	ui->tableViewZam->setItemDelegateForColumn(37, del);
	DelegateArrows *delArrow = new DelegateArrows(this);
	for (int i = 10; i < 25; i++) {
		ui->tableViewZam->setItemDelegateForColumn(i, delArrow);
	}
}

DoRozkrojuDialog::~DoRozkrojuDialog() {
	delete ui;
	if (model) {
		delete model;
	}
}

void DoRozkrojuDialog::on_buttonBox_accepted() {
	accept();
}

void DoRozkrojuDialog::on_buttonBox_rejected() {
	reject();
}

void DoRozkrojuDialog::showEvent(QShowEvent *e) {
	QAbstractItemModel *old = ui->tableViewZam->model();
	if (old) {
		delete old;
		old = 0;
	}
	ui->tableViewZam->setModel(model);
	QHeaderView *hv = ui->tableViewZam->horizontalHeader();
	hv->setSectionHidden(0, true);
	hv->setStretchLastSection(true);
	for (int i = 38; i < 47; i++) {
		hv->setSectionHidden(i, true);
	}
	hv->setDefaultAlignment(Qt::AlignLeft);
	for (int c = 9; c < 25;			++c) {
		ui->tableViewZam->setColumnWidth(c, 30);
	}
	ui->tableViewZam->setColumnWidth(25, 43); // suma
	ui->tableViewZam->setColumnWidth(1, 58);
	ui->tableViewZam->setColumnWidth(2, 84);
	ui->tableViewZam->setColumnWidth(3, 48);
	ui->tableViewZam->setColumnWidth(4, 50);
	ui->tableViewZam->setColumnWidth(5, 46);
	ui->tableViewZam->setColumnWidth(6, 46);
	ui->tableViewZam->setColumnWidth(7, 50);
	ui->tableViewZam->setColumnWidth(8, 50);
	ui->tableViewZam->setColumnWidth(9, 52);
	ui->tableViewZam->setColumnWidth(26, 56);// sk1
	ui->tableViewZam->setColumnWidth(27, 56);
	ui->tableViewZam->setColumnWidth(28, 56);
	ui->tableViewZam->setColumnWidth(29, 70);
	ui->tableViewZam->setColumnWidth(30, 70);
	ui->tableViewZam->setColumnWidth(31, 85);
	ui->tableViewZam->setColumnWidth(32, 80);

	ui->tableViewZam->setColumnWidth(33, 88);
	ui->tableViewZam->setColumnWidth(34, 88);
	ui->tableViewZam->setColumnWidth(37, 25);
	QStringList listaZamowienia;
	listaZamowienia  << "" << "NR ZAM" << "KLI SKRÓT" << "KLI NR"  << "WZÓR"  << "SPÓD" << "KOL" <<
			 "OCIEP" <<
			 "MAT" << "WKŁ" << "R36" << "R37" << "R38" << "R39" << "R40"	 << "R41" << "R42" << "R43"
			 << "R44" << "R45" << "R46" << "R47"	<< "R48" << "R49" << "R50"
			 << "SUMA"  << "SK1" <<	"SK2" <<	"SK3" << "SP NAZWA" <<
			 "SP PROD" << "UŻYTKOWNIK" << "HANDLOWIEC" << "DATA WPR" << "DATA REALIZ" << "UWAGI 1" << "UWAGI 2" << "DRUK" << ""
			 << "" << ""
			 << ""  << "" << ""
			 << ""  << "" << ""
			 << ""  << "" << ""
			 << ""  << "" << ""
			 << ""  << "" << ""
			 << "" << ""  << "" << "";
	for (int i = 0; i < model->columnCount(); ++i) {
		model->setHeaderData(i, Qt::Horizontal, listaZamowienia[i]);
	}
}

QStandardItemModel *DoRozkrojuDialog::getModel() const {
	return model;
}

void DoRozkrojuDialog::setModel(QStandardItemModel *value) {
	if (model) {
		delete model;
	}
	model = value;
}

void DoRozkrojuDialog::setZamowienia(const std::vector<int> &value) {
	zamowienia.clear();
	zamowienia = value;
}
