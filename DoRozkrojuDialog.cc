#include "DoRozkrojuDialog.h"
#include "ui_DoRozkrojuDialog.h"
#include "Delegate.h"
DoRozkrojuDialog::DoRozkrojuDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DoRozkrojuDialog), model(nullptr)
{
	ui->setupUi(this);
	//proxy = new QSortFilterProxyModel(this);
}

DoRozkrojuDialog::~DoRozkrojuDialog() {
	delete ui;
	//delete proxy;
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
	//	proxy->setDynamicSortFilter(true);
	//	proxy->setSourceModel(model);
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
	//	NotEditableDelegate *del = new NotEditableDelegate(this);
	//	for (int i = 0; i < 10; i++) {
	//		ui->tableViewZam->setItemDelegateForColumn(i, del);
	//	}
	//	for (int i = 25; i < 33; i++) {
	//		ui->tableViewZam->setItemDelegateForColumn(i, del);
	//	}
	//	ui->tableViewZam->setItemDelegateForColumn(37, del);
}

QAbstractItemModel *DoRozkrojuDialog::getModel() const {
	return model;
}

void DoRozkrojuDialog::setModel(QAbstractItemModel *value) {
	if (model) {
		delete model;
	}
	model = value;
}

void DoRozkrojuDialog::setZamowienia(const std::vector<int> &value) {
	zamowienia.clear();
	zamowienia = value;
}
