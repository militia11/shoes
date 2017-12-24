#include "wzoryDialog.h"
#include "ui_wzoryDialog.h"
#include <QInputDialog>
wzoryDialog::wzoryDialog(BazaDanychManager *db, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::wzoryDialog), dbManager(db)
{
	ui->setupUi(this);
	proxy = new QSortFilterProxyModel(this);
}

wzoryDialog::~wzoryDialog()
{	delete proxy;
	delete ui;
}

void wzoryDialog::showEvent(QShowEvent *e)
{
	Q_UNUSED(e);
	dbManager->setWzory();
	proxy->setSourceModel(dbManager->getWzory());
	proxy->setDynamicSortFilter(true);
	ui->tableView->setModel(proxy);
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignCenter);
	hv->setStretchLastSection(true);
}

void wzoryDialog::on_pushButton_2_clicked()
{
	int wzor = 0;

	wzor = QInputDialog::getInt(this, tr("NOWY WZÓR"),
					tr("Podaj nr wzoru."), QLineEdit::Normal);
	if (wzor != 0) {
		dbManager->dodajWzor(wzor);
		dbManager->getWzory()->select();
	}
}
